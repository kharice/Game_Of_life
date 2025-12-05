#include "Grille.hpp"
#include "EtatCellule.hpp"
#include "Rules.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <vector>

Grille::Grille() : largeur_(0), hauteur_(0) {} 
// constructeur par défaut : la grille n’a pas de taille, donc elle est vide

Grille::Grille(int largeur, int hauteur) : largeur_(largeur), hauteur_(hauteur) {
    initGrilleVide(); // on crée une grille direct avec toutes les cellules à 0 (mortes)
}

Grille::~Grille() {
    nettoyerGrille(); // quand on détruit l’objet, on libère toute la mémoire
}

Grille::Grille(const Grille& autre) : largeur_(0), hauteur_(0) {
    copierDepuis(autre); // constructeur de copie (on fait une copie de l’autre grille)
}

Grille& Grille::operator=(const Grille& autre) {
    if (this != &autre) { // éviter de faire une copie inutile de soi-même
        copierDepuis(autre);
    }
    return *this;
}

void Grille::copierDepuis(const Grille& autre) {
    nettoyerGrille(); // d'abord on enlève ce qu’il y avait avant
    
    largeur_ = autre.largeur_;
    hauteur_ = autre.hauteur_;
    
    if (largeur_ == 0 || hauteur_ == 0) return; // rien à copier si dimensions nulles
    
    tableauCellules_.resize(hauteur_); // on redimensionne pareil
    for (int y = 0; y < hauteur_; ++y) {
        tableauCellules_[y].resize(largeur_);
        for (int x = 0; x < largeur_; ++x) {
            // on recrée chaque cellule une par une
            // si elle était vivante dans l’autre grille, on refait une vivante
            // sinon une morte
            if (autre.tableauCellules_[y][x]->estVivante()) {
                tableauCellules_[y][x] = new CelluleVivante(x, y);
            } else {
                tableauCellules_[y][x] = new CelluleMorte(x, y);
            }
        }
    }
}

void Grille::nettoyerGrille() {
    // ici on supprime toutes les cases du tableau (pour éviter les fuites mémoire)
    for (size_t y = 0; y < tableauCellules_.size(); ++y) {
        for (size_t x = 0; x < tableauCellules_[y].size(); ++x) {
            if (tableauCellules_[y][x] != nullptr) {
                delete tableauCellules_[y][x]; // supprime la cellule
                tableauCellules_[y][x] = nullptr; // met un pointeur nul à la place
            }
        }
    }
    tableauCellules_.clear(); // on vide complètement le tableau
}

void Grille::initGrilleVide() {
    if (largeur_ == 0 || hauteur_ == 0) return; // si la taille est nulle → rien à faire
    
    nettoyerGrille(); // au cas où il y avait déjà quelque chose
    tableauCellules_.resize(hauteur_);
    
    for (int y = 0; y < hauteur_; ++y) {
        tableauCellules_[y].resize(largeur_);
        for (int x = 0; x < largeur_; ++x) {
            // on met une cellule morte partout au début
            tableauCellules_[y][x] = new CelluleMorte(x, y);
        }
    }
}

void Grille::chargerMotif(const std::string& nomFichier) {
    std::ifstream fichier(nomFichier); // on ouvre le fichier
    if (!fichier.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + nomFichier);
    }

    std::string premiereLigne;
    if (!std::getline(fichier, premiereLigne)) { // lit la première ligne
        throw std::runtime_error("Fichier vide ou illisible !");
    }

    // la première ligne contient la hauteur et la largeur
    std::stringstream ss(premiereLigne);
    int nvHauteur, nvLargeur;
    
    if (!(ss >> nvHauteur >> nvLargeur)) {
        throw std::runtime_error("Impossible de lire les dimensions !");
    }

    // on met à jour la taille de la grille
    largeur_ = nvLargeur;
    hauteur_ = nvHauteur;
    initGrilleVide(); // et on recrée une grille vide à cette taille

    std::string ligne;
    int y = 0;

    // ici on va lire toutes les lignes suivantes du fichier pour remplir la grille
    while (std::getline(fichier, ligne) && y < hauteur_) {
        std::stringstream ligneStream(ligne);
        int valeur;
        int x = 0;
        
        while (ligneStream >> valeur && x < largeur_) {
            if (valeur == 1) {
                // si la valeur vaut 1, ça veut dire "cellule vivante"
                delete tableauCellules_[y][x]; // on enlève l’ancienne cellule morte
                tableauCellules_[y][x] = new CelluleVivante(x, y); // on met une vivante
            }
            ++x;
        }
        ++y;
    }
    
    fichier.close(); // on ferme le fichier
}

int Grille::comptVoisinsVivants(int x, int y) const {
    int compte = 0;
    
    // on parcourt les 8 cases autour (les voisins)
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue; // on saute la cellule elle-même
            
            int nx = x + dx; // coordonnées du voisin
            int ny = y + dy;
            
            // vérifier que le voisin ne sort pas de la grille
            if (nx >= 0 && nx < largeur_ && ny >= 0 && ny < hauteur_) {
                if (tableauCellules_[ny][nx]->estVivante()) {
                    ++compte; // si vivant → on ajoute 1
                }
            }
        }
    }
    
    return compte; // on renvoie le total
}

void Grille::genSuivante() {
    // on prépare une nouvelle grille dans laquelle on va mettre le prochain état
    std::vector<std::vector<cellule*>> nouvelleGrille(hauteur_);
    
    for (int y = 0; y < hauteur_; ++y) {
        nouvelleGrille[y].resize(largeur_);
        for (int x = 0; x < largeur_; ++x) {
            int nbVoisins = comptVoisinsVivants(x, y); // on compte les voisins vivants
            
            // on applique les règles du jeu de la vie pour savoir si la cellule va vivre/mourir
            nouvelleGrille[y][x] = Rules::calculerProchainEtat(tableauCellules_[y][x], nbVoisins);
        }
    }
    
    // on supprime l'ancienne grille pour pas garder de vieux objets en mémoire
    for (int y = 0; y < hauteur_; ++y) {
        for (int x = 0; x < largeur_; ++x) {
            delete tableauCellules_[y][x];
        }
    }
    
    tableauCellules_ = nouvelleGrille; // la nouvelle grille devient la vraie grille
}

const cellule* Grille::getCellule(int x, int y) const {
    // vérifier que les coordonnées sont valides
    if (x >= 0 && x < largeur_ && y >= 0 && y < hauteur_) {
        return tableauCellules_[y][x];
    }
    return nullptr; // sinon on renvoie rien
}

void Grille::sauvegarder(const std::string& nomFichier) const {
    std::ofstream fichier(nomFichier);
    if (!fichier.is_open()) {
        throw std::runtime_error("Impossible de créer le fichier : " + nomFichier);
    }
    
    // première ligne : hauteur et largeur (comme dans les fichiers de motif)
    fichier << hauteur_ << " " << largeur_ << std::endl;
    
    // ensuite, on écrit toute la grille sous forme de 0 et 1
    for (int y = 0; y < hauteur_; ++y) {
        for (int x = 0; x < largeur_; ++x) {
            fichier << (tableauCellules_[y][x]->estVivante() ? 1 : 0);
            if (x < largeur_ - 1) fichier << " "; // espace entre les chiffres
        }
        fichier << std::endl;
    }
    
    fichier.close();
}

bool Grille::estIdentique(const Grille& autre) const {
    // si les dimensions ne sont pas les mêmes, on sait direct que ce n’est pas pareil
    if (largeur_ != autre.largeur_ || hauteur_ != autre.hauteur_) {
        std::cout << "Dimensions différentes : (" << hauteur_ << "x" << largeur_ 
                  << ") vs (" << autre.hauteur_ << "x" << autre.largeur_ << ")" << std::endl;
        return false;
    }
    
    // on compare chaque cellule
    for (int y = 0; y < hauteur_; ++y) {
        for (int x = 0; x < largeur_; ++x) {
            bool vivante1 = tableauCellules_[y][x]->estVivante();
            bool vivante2 = autre.tableauCellules_[y][x]->estVivante();
            
            // dès qu’il y a une cellule différente → les grilles ne sont pas identiques
            if (vivante1 != vivante2) {
                return false;
            }
        }
    }
    
    return true; // si on arrive jusque-là, c’est que tout est pareil
}
