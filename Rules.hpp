//Gestion des rèles de l'évolution des cellules
#ifndef RULES_HPP
#define RULES_HPP
#include "EtatCellule.hpp"
#include "cellule.hpp"

class Rules{
public :
    //cellule* : Pointeur vers la nouvelle cellule que l'on va créer (vivante ou morte)
    //celluleActuelle : Pointeur vers notre cellule actuelle(dont on veut calculer l'éta futur)
    //nbVoisinsVivants : Nombre de voisins vivants autour de la cellule actuelle
    static cellule* calculerProchainEtat(const cellule* celluleActuelle, int nbVoisinsVivants); 
    //Cette méthode va permettre de terminer l'état de la cellule pour la prochaine génération 
};

#endif
