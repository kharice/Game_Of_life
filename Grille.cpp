#include <vector> //Pour utiliser des vecteurs (pour les tableaux dynamiques)
#include <fstream> //Pour la gestion des fichiers
#include <stdexcept> //Pour gérer les erreurs de fichiers 
#include <string> //Pour gérer le nom du fichier 
#include <sstream> //Pour lire la première ligne du fichier 

#include "cellule.hpp"
#include "EtatCellule.hpp"
#include "Rules.hpp"
#include "Grille.hpp"

//On va remplir ici les instructions pour la méthode nettoyerGrille
void Grille::nettoyerGrille(){
    for (int y=0; y< hauteur_; ++y){ //Accès la ligne : index par la hauteur
        for (int x=0; x< largeur_;++x){
            //On va vérifier que le pointeur existe avant de tout supprimer
            if (tableauCellules_[y][x] !=nullptr){ //nullptr : pointeur nul
                 delete tableauCellules_[y][x]; 
                 tableauCellules_[y][x] = nullptr; //On remet alors le pointeur à 0
            }
        }
    }
    tableauCellules_.clear(); //On vide le tableau de pointeurs 
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
    if (!(ss>>nvLargeur>>nvHauteur)){
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
        for (int x =0; x<ligne.length() && x<largeur_; ++x){
            if (ligne[x]=='1'){
                //On remplace alors les cellules mortes qu'on a initialisé par des cellules vivantes 
                delete tableauCellules_[y][x]; //On supprime la mémoire qu'on a alloué à la cellule
                tableauCellules_[y][x] = new CelluleVivante(x,y); 
            }
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
