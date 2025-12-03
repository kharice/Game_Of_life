//Classe mère pour "Etat Cellule"
#ifndef CELLULE_HPP
#define CELLULE_HPP
#include <iostream>

class cellule{
public:
    virtual bool estVivante() const = 0; //Méthode virtuelle qui va permettre d'identifier l'état de la cellule
    cellule(int x, int y):x_(x), y_(y) {}; //Constructeur qui va prendre les coordonnées de la cellule 
    virtual ~cellule() = default; //Destructeur virtuel pour gérer les pointeurs 

    //Getters pour les coordonnées 
    int getX() const {return x_;}
    int getY() const {return y_;}
private :
    int x_, y_; //Coordonnées de la cellule
};

#endif
