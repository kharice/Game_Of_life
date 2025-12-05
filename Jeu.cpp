#include "Jeu.hpp"
#include "ModeConsole.hpp"
#include "ModeGraphique.hpp"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

Jeu::Jeu(const std::string& nomFichier) : nomFichierEntree_(nomFichier) {
    // On charge directement la grille à partir du fichier donné
    grille_.chargerMotif(nomFichier);
    
    // Ici on crée le nom du dossier où on va mettre les sorties
    // Le but est juste de garder le même nom que le fichier mais avec "_out" à la fin
    fs::path chemin = nomFichier;
    std::string nomBase = chemin.stem().string();  // stem() = le nom du fichier sans extension
    nomDossierSortie_ = nomBase + "_out";
}

void Jeu::executerModeConsole(int nbIterations) {
    // On crée un mode console, en lui donnant la grille + le dossier de sortie
    ModeConsole modeConsole(grille_, nomDossierSortie_);
    
    // Ensuite on lance la simulation en console
    modeConsole.executerSimulation(nbIterations);
}

void Jeu::executerModeGraphique() {
    // FPS_CIBLE = vitesse d’affichage (5 images par seconde ici)
    const float FPS_CIBLE = 5.0f;
    
    // On crée le mode graphique
    ModeGraphique modeGraphique(grille_, FPS_CIBLE);
    
    // On démarre la simulation avec une fenêtre
    modeGraphique.run(grille_);
}

bool Jeu::testUnitaire(const std::string& fichierInitial, int nbIterations, const std::string& fichierAttendu) {
    std::cout << "\n=== Test Unitaire ===" << std::endl;
    std::cout << "Fichier initial : " << fichierInitial << std::endl;
    std::cout << "Nombre d'itérations : " << nbIterations << std::endl;
    std::cout << "Fichier attendu : " << fichierAttendu << std::endl;
    
    try {
        Grille grilleTest;
        
        // On charge la grille initiale pour commencer le test
        grilleTest.chargerMotif(fichierInitial);
        
        // On simule toutes les itérations demandées
        for (int i = 0; i < nbIterations; ++i) {
            grilleTest.genSuivante();
        }
        
        // On charge la grille qui contient le résultat attendu
        Grille grilleAttendue;
        grilleAttendue.chargerMotif(fichierAttendu);
        
        // Ici on compare les deux grilles
        bool resultat = grilleTest.estIdentique(grilleAttendue);
        
        // On affiche si c’est bon ou pas
        if (resultat) {
            std::cout << " Test RÉUSSI" << std::endl;
        } else {
            std::cout << " Test ÉCHOUÉ" << std::endl;
        }
        
        return resultat;
        
    } catch (const std::exception& e) {
        // En cas de crash ou problème, on affiche l’erreur
        std::cerr << "Erreur lors du test : " << e.what() << std::endl;
        return false;
    }
}
