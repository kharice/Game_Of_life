#include "Grille.hpp"
#include "EtatCellule.hpp"
#include "Rules.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <vector>

Grille::Grille() : largeur_(0), hauteur_(0) {}

Grille::Grille(int largeur, int hauteur) : largeur_(largeur), hauteur_(hauteur) {
    initGrilleVide();
}

Grille::~Grille() {
    nettoyerGrille();
}

Grille::Grille(const Grille& autre) : largeur_(0), hauteur_(0) {
    copierDepuis(autre);
}

Grille& Grille::operator=(const Grille& autre) {
    if (this != &autre) {
        copierDepuis(autre);
    }
    return *this;
}

void Grille::copierDepuis(const Grille& autre) {
    nettoyerGrille();
    
    largeur_ = autre.largeur_;
    hauteur_ = autre.hauteur_;
    
    if (largeur_ == 0 || hauteur_ == 0) return;
    
    tableauCellules_.resize(hauteur_);
    for (int y = 0; y < hauteur_; ++y) {
        tableauCellules_[y].resize(largeur_);
        for (int x = 0; x < largeur_; ++x) {
            if (autre.tableauCellules_[y][x]->estVivante()) {
                tableauCellules_[y][x] = new CelluleVivante(x, y);
            } else {
                tableauCellules_[y][x] = new CelluleMorte(x, y);
            }
        }
    }
}

void Grille::nettoyerGrille() {
    for (size_t y = 0; y < tableauCellules_.size(); ++y) {
        for (size_t x = 0; x < tableauCellules_[y].size(); ++x) {
            if (tableauCellules_[y][x] != nullptr) {
                delete tableauCellules_[y][x];
                tableauCellules_[y][x] = nullptr;
            }
        }
    }
    tableauCellules_.clear();
}

void Grille::initGrilleVide() {
    if (largeur_ == 0 || hauteur_ == 0) return;
    
    nettoyerGrille();
    tableauCellules_.resize(hauteur_);
    
    for (int y = 0; y < hauteur_; ++y) {
        tableauCellules_[y].resize(largeur_);
        for (int x = 0; x < largeur_; ++x) {
            tableauCellules_[y][x] = new CelluleMorte(x, y);
        }
    }
}

void Grille::chargerMotif(const std::string& nomFichier) {
    std::ifstream fichier(nomFichier);
    if (!fichier.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + nomFichier);
    }

    std::string premiereLigne;
    if (!std::getline(fichier, premiereLigne)) {
        throw std::runtime_error("Fichier vide ou illisible !");
    }

    std::stringstream ss(premiereLigne);
    int nvHauteur, nvLargeur;
    
    if (!(ss >> nvHauteur >> nvLargeur)) {
        throw std::runtime_error("Impossible de lire les dimensions !");
    }

    largeur_ = nvLargeur;
    hauteur_ = nvHauteur;
    initGrilleVide();

    std::string ligne;
    int y = 0;

    while (std::getline(fichier, ligne) && y < hauteur_) {
        std::stringstream ligneStream(ligne);
        int valeur;
        int x = 0;
        
        while (ligneStream >> valeur && x < largeur_) {
            if (valeur == 1) {
                delete tableauCellules_[y][x];
                tableauCellules_[y][x] = new CelluleVivante(x, y);
            }
            ++x;
        }
        ++y;
    }
    
    fichier.close();
}

int Grille::comptVoisinsVivants(int x, int y) const {
    int compte = 0;
    
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;
            
            int nx = x + dx;
            int ny = y + dy;
            
            if (nx >= 0 && nx < largeur_ && ny >= 0 && ny < hauteur_) {
                if (tableauCellules_[ny][nx]->estVivante()) {
                    ++compte;
                }
            }
        }
    }
    
    return compte;
}

void Grille::genSuivante() {
    std::vector<std::vector<cellule*>> nouvelleGrille(hauteur_);
    
    for (int y = 0; y < hauteur_; ++y) {
        nouvelleGrille[y].resize(largeur_);
        for (int x = 0; x < largeur_; ++x) {
            int nbVoisins = comptVoisinsVivants(x, y);
            nouvelleGrille[y][x] = Rules::calculerProchainEtat(tableauCellules_[y][x], nbVoisins);
        }
    }
    
    // Libérer l'ancienne grille
    for (int y = 0; y < hauteur_; ++y) {
        for (int x = 0; x < largeur_; ++x) {
            delete tableauCellules_[y][x];
        }
    }
    
    tableauCellules_ = nouvelleGrille;
}

const cellule* Grille::getCellule(int x, int y) const {
    if (x >= 0 && x < largeur_ && y >= 0 && y < hauteur_) {
        return tableauCellules_[y][x];
    }
    return nullptr;
}

void Grille::sauvegarder(const std::string& nomFichier) const {
    std::ofstream fichier(nomFichier);
    if (!fichier.is_open()) {
        throw std::runtime_error("Impossible de créer le fichier : " + nomFichier);
    }
    
    fichier << hauteur_ << " " << largeur_ << std::endl;
    
    for (int y = 0; y < hauteur_; ++y) {
        for (int x = 0; x < largeur_; ++x) {
            fichier << (tableauCellules_[y][x]->estVivante() ? 1 : 0);
            if (x < largeur_ - 1) fichier << " ";
        }
        fichier << std::endl;
    }
    
    fichier.close();
}

bool Grille::estIdentique(const Grille& autre) const {
    if (largeur_ != autre.largeur_ || hauteur_ != autre.hauteur_) {
        std::cout << "Dimensions différentes : (" << hauteur_ << "x" << largeur_ 
                  << ") vs (" << autre.hauteur_ << "x" << autre.largeur_ << ")" << std::endl;
        return false;
    }
    
    for (int y = 0; y < hauteur_; ++y) {
        for (int x = 0; x < largeur_; ++x) {
            bool vivante1 = tableauCellules_[y][x]->estVivante();
            bool vivante2 = autre.tableauCellules_[y][x]->estVivante();
            if (vivante1 != vivante2) {
                return false;
            }
        }
    }
    
    return true;
}
