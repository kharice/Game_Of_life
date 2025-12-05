#include <iostream>
#include <string>
#include <limits>
#include "Jeu.hpp"

void viderBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main(int argc, char* argv[]) {
    std::cout << "=== JEU DE LA VIE ===" << std::endl;
    std::cout << std::endl;
    
    // Demander le fichier d'entrée
    std::string nomFichierEntree;
    if (argc == 2) {
        nomFichierEntree = argv[1];
    } else {
        std::cout << "Entrez le nom du fichier d'entrée : ";
        std::cin >> nomFichierEntree;
    }
    
    // Demander le mode d'exécution
    std::string mode;
    std::cout << "\nChoisissez le mode d'exécution :" << std::endl;
    std::cout << "  1. console" << std::endl;
    std::cout << "  2. graphique" << std::endl;
    std::cout << "  3. test unitaire" << std::endl;
    std::cout << "Votre choix : ";
    std::cin >> mode;
    
    try {
        if (mode == "1" || mode == "console") {
            int iterations;
            std::cout << "\nEntrez le nombre d'itérations à effectuer : ";
            
            while (!(std::cin >> iterations) || iterations < 0) {
                std::cerr << "Erreur : veuillez saisir un nombre entier positif." << std::endl;
                viderBuffer();
                std::cout << "Entrez le nombre d'itérations à effectuer : ";
            }
            
            std::cout << "\n---- Début de la simulation en mode CONSOLE ----" << std::endl;
            Jeu jeu(nomFichierEntree);
            jeu.executerModeConsole(iterations);
            std::cout << "\n---- Simulation terminée ----" << std::endl;
            
        } else if (mode == "2" || mode == "graphique") {
            std::cout << "\n---- Début de la simulation en mode GRAPHIQUE ----" << std::endl;
            Jeu jeu(nomFichierEntree);
            jeu.executerModeGraphique();
            std::cout << "\n---- Simulation terminée ----" << std::endl;
            
        } else if (mode == "3" || mode == "test" || mode == "test unitaire") {
            int nbIterations;
            std::string fichierAttendu;
            
            std::cout << "\nEntrez le nombre d'itérations pour le test : ";
            while (!(std::cin >> nbIterations) || nbIterations < 0) {
                std::cerr << "Erreur : veuillez saisir un nombre entier positif." << std::endl;
                viderBuffer();
                std::cout << "Entrez le nombre d'itérations : ";
            }
            
            std::cout << "Entrez le nom du fichier avec le résultat attendu : ";
            std::cin >> fichierAttendu;
            
            bool resultat = Jeu::testUnitaire(nomFichierEntree, nbIterations, fichierAttendu);
            
            return resultat ? 0 : 1;
            
        } else {
            std::cerr << "Mode non reconnu ! Utilisez 'console', 'graphique' ou 'test unitaire'." << std::endl;
            return 1;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "\nErreur : " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
