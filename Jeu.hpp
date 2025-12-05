#ifndef JEU_HPP
#define JEU_HPP

#include <string>
#include "Grille.hpp"

class Jeu {
private:
    Grille grille_;
    std::string nomFichierEntree_;
    std::string nomDossierSortie_;

public:
    Jeu(const std::string& nomFichier);
    
    void executerModeConsole(int nbIterations);
    void executerModeGraphique();
    
    static bool testUnitaire(const std::string& fichierInitial, int nbIterations, const std::string& fichierAttendu);
};

#endif
