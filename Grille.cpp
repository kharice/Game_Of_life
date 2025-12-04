#include <vector> //Pour utiliser des vecteurs (pour les tableaux dynamiques)
#include <fstream> //Pour la gestion des fichiers
#include <stdexcept> //Pour gérer les erreurs de fichiers 
#include <string> //Pour gérer le nom du fichier 
#include <sstream> //Pour lire la première ligne du fichier 
#include <utility>
#include <filesystem>

#include "cellule.hpp"
#include "EtatCellule.hpp"
#include "Rules.hpp"
#include "Grille.hpp"

//On va remplir ici les instructions pour la méthode nettoyerGrille
void Grille::nettoyerGrille(){
    if (tableauCellules_.empty()){
        return;
    }
    //On va utiliser la taille réelle du tableau 
    for (size_t y=0; y< tableauCellules_.size(); ++y){ //Accès la ligne : index par la hauteur
        for (size_t x=0; x< tableauCellules_[y].size();++x){
            //On va vérifier que le pointeur existe avant de tout supprimer
            if (tableauCellules_[y][x] !=nullptr){ //nullptr : pointeur nul
                 delete tableauCellules_[y][x]; 
                 tableauCellules_[y][x] = nullptr; //On remet alors le pointeur à 0
            }
        }
    }
    tableauCellules_.clear(); //On vide le tableau de pointeurs 
}

Grille::~Grille() {
    nettoyerGrille();
}

void Grille::chargerMotif(const std::string& nomFichier){
    std::ifstream fichier(nomFichier);
    if (!fichier.is_open()){ //On vérifie si le fichier est bien ouvert 
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + nomFichier);  
    }
    std::string premiereLigne; //Variable où on va stocker la première ligne du fichier texte
    if (!std::getline(fichier, premiereLigne)){ //On va vérifier si on arrive bien à prendre la première ligne
        throw std::runtime_error("Fichier video ou illisible !");
    }
    std::stringstream ss(premiereLigne);
    int nvLargeur, nvHauteur; //On récupère les nouvelles dimensions depuis la première ligne 
    
    //Pour vérifier la bonne lecture des dimensions (Deux entiers séparés d'un espace) :
    if (!(ss>>nvHauteur>>nvLargeur)){
        throw std::runtime_error("Impossible de lire les dimensions, vérifiez le format !");
    }
    //On va alors mettre à jour les dimensions de la grille
    largeur_=nvLargeur;
    hauteur_=nvHauteur;
    
    //Préparation de la grille pour nos nouvelles dimensions 
    initGrilleVide();
    std::string ligne; 
    int y =0; 

    //On va maintenant lire la suite du fichier, c.a.d le "motif" 
    while(std::getline(fichier, ligne) && y<hauteur_){
        //On va créer un compteur d'index de grille 
        int x_grille=0;
        //On va faire une boucle pour tous les carcatères lus :
        for (char c : ligne){
            if (c==' '  || c =='\t'){
                continue; //On passe au carctère suivant sans incrémenter x_grille
            }
            //Ensuit on va vérifier les limites de la grille 
            if (x_grille>= largeur_){
                break; //On s'arrête quand on a lu toutes les colonnes
            }
            if (c=='1'){
                //On remplace alors les cellules mortes qu'on a initialisé par des cellules vivantes 
                delete tableauCellules_[y][x_grille]; //On supprime la mémoire qu'on a alloué à la cellule
                tableauCellules_[y][x_grille] = new CelluleVivante(x_grille,y); 
            }
            //Avançons à la colonne suivante 
            x_grille++;
            //NB : Si on a 0 on ne fait rien parce que la cellule est déjà morte 
        }
        ++y;
    }
    fichier.close(); //On ferme le fichier après lecture
}

Grille::Grille(int largeur, int hauteur):largeur_(largeur), hauteur_(hauteur){
    initGrilleVide();
}
void Grille::initGrilleVide()
{
    //Si les dimensions de la grille sont déjà nulles on ne fait rien 
    if (largeur_==0|| hauteur_==0) return; 
    //On nettoie l'ancienne grille
    nettoyerGrille();
    //On redimensionne selon largeur et hauteur 
    tableauCellules_.resize(hauteur_); 
    //On remplit avec de nouvelles cellules mortes
    for (int y=0; y<hauteur_; ++y){
        tableauCellules_[y].resize(largeur_);
        for (int x=0; x<largeur_; ++x){
            tableauCellules_[y][x]= new CelluleMorte(x,y);
        }
    }
}

int Grille::comptVoisinsVivants(int x, int y) const {
    int voisinsVivants = 0;
    
    // Boucle de voisinage : parcourt les 8 cellules adjacentes
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            
            if (dx == 0 && dy == 0) continue; // Ignorer la cellule elle-même
            
            int nx = x + dx; // Coordonnée X du voisin
            int ny = y + dy; // Coordonnée Y du voisin
            
            // Vérifier les limites de la grille
            if (nx >= 0 && nx < largeur_ && ny >= 0 && ny < hauteur_) {
                
                // Utilisation de la méthode de la cellule
                if (tableauCellules_[ny][nx]->estVivante()) {
                    voisinsVivants++;
                }
            }
        }
    }
    return voisinsVivants;
}

void Grille::genSuivante() {
    
    // Si la grille n'a pas de dimensions, on ne fait rien
    if (largeur_ == 0 || hauteur_ == 0) return;
    
    // 1. Création d'une grille temporaire pour stocker les nouveaux états.
    // L'inclusion de <utility> est nécessaire pour std::move (fait en haut).
    std::vector<std::vector<cellule*>> tableauNouvellesCellules;
    tableauNouvellesCellules.resize(hauteur_);
    
    // 2. Parcourir toutes les cellules de la grille actuelle (tableauCellules_)
    for (int y = 0; y < hauteur_; ++y) {
        tableauNouvellesCellules[y].resize(largeur_);
        
        for (int x = 0; x < largeur_; ++x) {
            
            // a) Compter les voisins vivants en appelant la méthode privée dédiée
            int nbVoisinsVivants = comptVoisinsVivants(x, y); 
            
            // b) Obtenir la cellule actuelle pour la passer à la fonction de règle
            const cellule* celluleActuelle = tableauCellules_[y][x];
            
            // CRITIQUE : Appel de la méthode statique (la seule correcte)
            // L'objet Cellule* est alloué (new) par Rules::calculerProchainEtat
            cellule* nouvelleCellule = Rules::calculerProchainEtat(celluleActuelle, nbVoisinsVivants); 
            
            // c) Stocker le pointeur vers la nouvelle cellule créée
            tableauNouvellesCellules[y][x] = nouvelleCellule;
        }
    }

    // 3. Remplacer l'ancienne grille par la nouvelle
    
    // a) Libérer la mémoire de toutes les anciennes cellules
    nettoyerGrille(); 

    // b) Remplacer le tableau de pointeurs
    tableauCellules_ = std::move(tableauNouvellesCellules); 
}

// Grille.cpp (AJOUTER cette fonction)

const cellule* Grille::getCellule(int x, int y) const {
    // Vérification des limites pour éviter un crash et respecter la déclaration const
    if (x >= 0 && x < largeur_ && y >= 0 && y < hauteur_) {
        // Retourne la cellule. L'index est [y][x] pour une matrice standard
        return tableauCellules_[y][x];
    }
    // Retourne un pointeur nul si les coordonnées sont invalides
    return nullptr;
}
