#include "ModeConsole.hpp"
#include <filesystem>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace fs = std::filesystem;

ModeConsole::ModeConsole(Grille& grille, const std::string& nomDossierSortie)
    : grille_(grille), nomDossierSortie_(nomDossierSortie) {
}

void ModeConsole::creerDossierSortie() {
    if (!fs::exists(nomDossierSortie_)) {
        fs::create_directory(nomDossierSortie_);
        std::cout << "Dossier créé : " << nomDossierSortie_ << std::endl;
    } else {
        std::cout << "Le dossier existe déjà : " << nomDossierSortie_ << std::endl;
    }
}

void ModeConsole::sauvegarderIteration(int numeroIteration) {
    std::stringstream nomFichier;
    nomFichier << nomDossierSortie_ << "/iteration_" 
               << std::setw(3) << std::setfill('0') << numeroIteration << ".txt";
    
    grille_.sauvegarder(nomFichier.str());
    std::cout << "Itération " << numeroIteration << " sauvegardée" << std::endl;
}

void ModeConsole::executerSimulation(int nbIterations) {
    creerDossierSortie();
    
    // Sauvegarder l'état initial (itération 0)
    sauvegarderIteration(0);
    
    bool stable = false;
    
    // Exécuter les itérations
    for (int i = 1; i <= nbIterations && !stable; ++i) {
        // Copier l'état actuel avant de générer le suivant
        Grille grillePrec = grille_;
        
        grille_.genSuivante();
        sauvegarderIteration(i);
        
        // Vérifier si la grille est stable
        if (grille_.estIdentique(grillePrec)) {
            std::cout << "\n⚠ La grille est stable à l'itération " << i << std::endl;
            std::cout << "La simulation s'arrête car il n'y a plus d'évolution." << std::endl;
            stable = true;
        }
    }
    
    std::cout << "\n✓ Simulation terminée avec succès !" << std::endl;
    std::cout << "Résultats sauvegardés dans : " << nomDossierSortie_ << std::endl;
}
