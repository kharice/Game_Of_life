//Gère l'état des cellules
#ifndef ETATCELLULE_HPP
#define ETATCELLULE_HPP
#include "cellule.hpp"

class CelluleVivante : public cellule {
    public:
        CelluleVivante (int x, int y):cellule(x,y){}; //Constructeur qui va appeler les coordonnées de la classe de base 
        bool estVivante() const override{return true;} // On utilise ici la méthode virtuelle de Cellule pour vérifier si elle est vivante ou pas 
};

class CelluleMorte : public cellule{
    public :
        CelluleMorte (int x, int y): cellule(x,y){}; //Comme pour CelluleVivante on va récuperer les coordonnées de cellules
        bool estVivante() const override{return false;} //On va aussi réétuliser la méthode virtuelle pour définir l'état de la cellule à morte cette fois-ci 
};
#endif
