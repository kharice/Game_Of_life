#ifndef ETATCELLULE_HPP
#define ETATCELLULE_HPP

#include "cellule.hpp"

class CelluleVivante : public cellule {
public:
    CelluleVivante(int x, int y) : cellule(x, y) {}
    bool estVivante() const override { return true; }
};

class CelluleMorte : public cellule {
public:
    CelluleMorte(int x, int y) : cellule(x, y) {}
    bool estVivante() const override { return false; }
};

#endif
