#ifndef JEU_HPP
#define JEU_HPP

#include <string>
#include "Grille.hpp"

// Classe principale du programme : c'est elle qui contrôle tout le jeu,
// charge la grille, choisit le mode d'exécution, etc.
class Jeu {
private:
    Grille grille_;               // la grille du jeu (état courant)
    std::string nomFichierEntree_; // nom du fichier qu'on lit au début pour charger la grille
    std::string nomDossierSortie_; // nom du dossier où on met les résultats en mode console

public:
    // constructeur : prend juste le nom du fichier qui contient la grille de départ
    Jeu(const std::string& nomFichier);
    
    // exécute la simulation en mode console (sauvegarde dans des fichiers .txt)
    void executerModeConsole(int nbIterations);

    // lance l'interface graphique pour afficher la grille en direct
    void executerModeGraphique();
    
    // fonction spéciale pour faire un test automatique :
    // elle compare le résultat obtenu avec un fichier attendu
    // et renvoie true si tout correspond
    static bool testUnitaire(const std::string& fichierInitial, int nbIterations, const std::string& fichierAttendu);
};

#endif
