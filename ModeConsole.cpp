#include "ModeConsole.hpp"
#include <filesystem>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace fs = std::filesystem; 
// raccourci pour éviter d'écrire std::filesystem tout le temps

ModeConsole::ModeConsole(Grille& grille, const std::string& nomDossierSortie)
    : grille_(grille), nomDossierSortie_(nomDossierSortie) {
    // constructeur : on récupère la grille et le nom du dossier où on va tout sauver
}

void ModeConsole::creerDossierSortie() {
    // on vérifie si le dossier existe déjà (pour pas le recréer)
    if (!fs::exists(nomDossierSortie_)) {
        fs::create_directory(nomDossierSortie_); // on crée le dossier
        std::cout << "Dossier créé : " << nomDossierSortie_ << std::endl;
    } else {
        std::cout << "Le dossier existe déjà : " << nomDossierSortie_ << std::endl;
    }
}

void ModeConsole::sauvegarderIteration(int numeroIteration) {
    // ici on fabrique un nom de fichier du style : iteration_003.txt
    std::stringstream nomFichier;
    nomFichier << nomDossierSortie_ << "/iteration_" 
               << std::setw(3) << std::setfill('0') << numeroIteration << ".txt";
               // setw(3) = 3 chiffres / setfill('0') = rajoute des 0 devant

    grille_.sauvegarder(nomFichier.str()); 
    // on demande à la grille de se sauvegarder dans ce fichier

    std::cout << "Itération " << numeroIteration << " sauvegardée" << std::endl;
}

void ModeConsole::executerSimulation(int nbIterations) {
    creerDossierSortie(); // d’abord on s’assure que le dossier existe
    
    // Sauvegarder l'état initial (itération 0)
    sauvegarderIteration(0); // avant de commencer, on garde la grille de départ
    
    bool stable = false; // pour savoir si la grille ne change plus
    
    // Exécuter les itérations
    for (int i = 1; i <= nbIterations && !stable; ++i) {
        // On fait une copie de la grille actuelle pour comparer après
        Grille grillePrec = grille_;  // copie complète de la grille
        
        grille_.genSuivante(); // on passe à l'état suivant (jeu de la vie)
        sauvegarderIteration(i); // on sauvegarde ce nouvel état
        
        // Vérifier si la grille a changé ou pas
        if (grille_.estIdentique(grillePrec)) {
            // si c’est identique → ça veut dire qu'il n'y a plus d'évolution
            std::cout << "\n La grille est stable à l'itération " << i << std::endl;
            std::cout << "La simulation s'arrête car il n'y a plus d'évolution." << std::endl;
            stable = true; // on arrête la boucle
        }
    }
    
    // Quand la boucle est finie (soit on a atteint nbIterations, soit grille stable)
    std::cout << "\n Simulation terminée avec succès !" << std::endl;
    std::cout << "Résultats sauvegardés dans : " << nomDossierSortie_ << std::endl;
}
