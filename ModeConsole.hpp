#ifndef MODECONSOLE_HPP
#define MODECONSOLE_HPP

#include <string>
#include "Grille.hpp"

// Classe qui s’occupe de gérer la simulation mais en mode "console"
// (donc sans interface graphique, juste en sauvegardant les fichiers)
class ModeConsole {
private:
    Grille& grille_;               // référence vers la grille qu’on va simuler
    std::string nomDossierSortie_; // nom du dossier où on va mettre les fichiers .txt
    
    // fonction qui crée le dossier si jamais il n’existe pas déjà
    void creerDossierSortie();

    // fonction qui sauvegarde un état de la grille (appelée à chaque itération)
    void sauvegarderIteration(int numeroIteration);

public:
    // constructeur : on donne la grille sur laquelle travailler + le dossier de sortie
    ModeConsole(Grille& grille, const std::string& nomDossierSortie);
    
    // lance toute la simulation pendant un certain nombre d’itérations
    void executerSimulation(int nbIterations);
};

#endif
