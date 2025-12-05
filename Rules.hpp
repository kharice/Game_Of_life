#ifndef RULES_HPP
#define RULES_HPP

#include "cellule.hpp"

class Rules {
public:
    static cellule* calculerProchainEtat(const cellule* celluleActuelle, int nbVoisinsVivants);
};

#endif
