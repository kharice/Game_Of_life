#ifndef RULES_HPP
#define RULES_HPP

#include "cellule.hpp"

// Classe qui contient les règles du Jeu de la Vie
class Rules {
public:
    // Fonction statique car on n'a pas besoin de créer un objet Rules pour l'utiliser.
    // On lui donne la cellule actuelle + le nombre de voisins vivants,
    // et elle renvoie une nouvelle cellule qui représente son état à la prochaine génération.
    static cellule* calculerProchainEtat(const cellule* celluleActuelle, int nbVoisinsVivants);
};

#endif
