#ifndef GRILLE_HPP
#define GRILLE_HPP

#include <vector>
#include <string>
#include "cellule.hpp"

class Grille {
private:
    int largeur_;
    int hauteur_;
    std::vector<std::vector<cellule*>> tableauCellules_;
    
    int comptVoisinsVivants(int x, int y) const;
    void nettoyerGrille();
    void initGrilleVide();
    void copierDepuis(const Grille& autre);

public:
    Grille();
    Grille(int largeur, int hauteur);
    ~Grille();
    
    Grille(const Grille& autre);
    Grille& operator=(const Grille& autre);

    void chargerMotif(const std::string& nomFichier);
    void genSuivante();
    void sauvegarder(const std::string& nomFichier) const;
    
    int getLargeur() const { return largeur_; }
    int getHauteur() const { return hauteur_; }
    const cellule* getCellule(int x, int y) const;
    
    bool estIdentique(const Grille& autre) const;
};

#endif
