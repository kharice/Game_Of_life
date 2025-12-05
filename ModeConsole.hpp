#ifndef MODECONSOLE_HPP
#define MODECONSOLE_HPP

#include <string>
#include "Grille.hpp"

class ModeConsole {
private:
    Grille& grille_;
    std::string nomDossierSortie_;
    
    void creerDossierSortie();
    void sauvegarderIteration(int numeroIteration);

public:
    ModeConsole(Grille& grille, const std::string& nomDossierSortie);
    
    void executerSimulation(int nbIterations);
};

#endif
