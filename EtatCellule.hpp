#ifndef ETATCELLULE_HPP
#define ETATCELLULE_HPP

// Inclusion de la définition de la classe de base "cellule"
#include "cellule.hpp"

// Classe représentant une cellule vivante
class CelluleVivante : public cellule {
public:
    // Constructeur : initialise la cellule avec ses coordonnées (x, y)
    // Appelle le constructeur de la classe de base "cellule"
    CelluleVivante(int x, int y) : cellule(x, y) {}

    // Méthode qui indique que cette cellule est vivante
    // Redéfinition (override) de la méthode virtuelle de la classe de base
    bool estVivante() const override { return true; }
};

// Classe représentant une cellule morte
class CelluleMorte : public cellule {
public:
    // Constructeur : initialise la cellule avec ses coordonnées (x, y)
    // Appelle le constructeur de la classe de base "cellule"
    CelluleMorte(int x, int y) : cellule(x, y) {}

    // Méthode qui indique que cette cellule est morte
    // Redéfinition (override) de la méthode virtuelle de la classe de base
    bool estVivante() const override { return false; }
};

#endif 
