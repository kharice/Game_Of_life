#include "Jeu.hpp"
#include "ModeConsole.hpp"
#include "ModeGraphique.hpp"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

Jeu::Jeu(const std::string& nomFichier) : nomFichierEntree_(nomFichier) {
    grille_.chargerMotif(nomFichier);
    
    // Créer le nom du dossier de sortie
    fs::path chemin = nomFichier;
    std::string nomBase = chemin.stem().string();
    nomDossierSortie_ = nomBase + "_out";
}

void Jeu::executerModeConsole(int nbIterations) {
    ModeConsole modeConsole(grille_, nomDossierSortie_);
    modeConsole.executerSimulation(nbIterations);
}

void Jeu::executerModeGraphique() {
    ModeGraphique modeGraphique(grille_, 10.0f);
    modeGraphique.run(grille_);
}

bool Jeu::testUnitaire(const std::string& fichierInitial, int nbIterations, const std::string& fichierAttendu) {
    std::cout << "\n=== Test Unitaire ===" << std::endl;
    std::cout << "Fichier initial : " << fichierInitial << std::endl;
    std::cout << "Nombre d'itérations : " << nbIterations << std::endl;
    std::cout << "Fichier attendu : " << fichierAttendu << std::endl;
    
    try {
        Grille grilleTest;
        grilleTest.chargerMotif(fichierInitial);
        
        for (int i = 0; i < nbIterations; ++i) {
            grilleTest.genSuivante();
        }
        
        Grille grilleAttendue;
        grilleAttendue.chargerMotif(fichierAttendu);
        
        bool resultat = grilleTest.estIdentique(grilleAttendue);
        
        if (resultat) {
            std::cout << "✓ Test RÉUSSI" << std::endl;
        } else {
            std::cout << "✗ Test ÉCHOUÉ" << std::endl;
        }
        
        return resultat;
        
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors du test : " << e.what() << std::endl;
        return false;
    }
}
