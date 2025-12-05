#include <iostream>
#include <string>
#include <limits>
#include "Jeu.hpp"

// Fonction pour vider le buffer du cin quand l'utilisateur tape n'importe quoi.
// Sinon cin reste bloqué et on ne peut plus saisir correctement.
void viderBuffer() {
    std::cin.clear(); // remet cin dans un état normal
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // vide tout ce qu'il y a en attente
}

int main(int argc, char* argv[]) {
    std::cout << "=== JEU DE LA VIE ===" << std::endl;
    std::cout << std::endl;
    
    // On récupère le fichier d’entrée, soit dans les arguments du programme,
    // soit en demandant directement à l’utilisateur.
    std::string nomFichierEntree;
    if (argc == 2) {
        nomFichierEntree = argv[1]; // si l’utilisateur a lancé le programme avec un argument
    } else {
        std::cout << "Entrez le nom du fichier d'entrée : ";
        std::cin >> nomFichierEntree;
    }
    
    // On demande dans quel mode il veut exécuter le jeu.
    std::string mode;
    std::cout << "\nChoisissez le mode d'exécution :" << std::endl;
    std::cout << "  1. console" << std::endl;
    std::cout << "  2. graphique" << std::endl;
    std::cout << "  3. test unitaire" << std::endl;
    std::cout << "Votre choix : ";
    std::cin >> mode;
    
    try {
        // Mode console (affichage texte + sauvegarde des fichiers)
        if (mode == "1" || mode == "console") {
            int iterations;
            std::cout << "\nEntrez le nombre d'itérations à effectuer : ";
            
            // ici on vérifie que l’utilisateur entre un vrai nombre positif
            while (!(std::cin >> iterations) || iterations < 0) {
                std::cerr << "Erreur : veuillez saisir un nombre entier positif." << std::endl;
                viderBuffer();
                std::cout << "Entrez le nombre d'itérations à effectuer : ";
            }
            
            std::cout << "\n---- Début de la simulation en mode CONSOLE ----" << std::endl;
            Jeu jeu(nomFichierEntree); // on charge le jeu à partir du fichier
            jeu.executerModeConsole(iterations); // on lance la version console
            std::cout << "\n---- Simulation terminée ----" << std::endl;
            
        }
        // Mode graphique (fenêtre SFML)
        else if (mode == "2" || mode == "graphique") {
            std::cout << "\n---- Début de la simulation en mode GRAPHIQUE ----" << std::endl;
            Jeu jeu(nomFichierEntree);
            jeu.executerModeGraphique(); // ici on ouvre une fenêtre SFML
            std::cout << "\n---- Simulation terminée ----" << std::endl;
            
        }
        // Mode test unitaire (compare automatiquement un résultat avec un fichier attendu)
        else if (mode == "3" || mode == "test" || mode == "test unitaire") {
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

            // On appelle la fonction statique qui compare le résultat obtenu avec le fichier attendu
            bool resultat = Jeu::testUnitaire(nomFichierEntree, nbIterations, fichierAttendu);
            
            return resultat ? 0 : 1; // si le test échoue, on renvoie 1
            
        }
        // Si l’utilisateur tape un truc qui ne correspond à rien
        else {
            std::cerr << "Mode non reconnu ! Utilisez 'console', 'graphique' ou 'test unitaire'." << std::endl;
            return 1;
        }
        
    } catch (const std::exception& e) {
        // Si jamais quelque chose plante dans le code, on affiche l’erreur.
        std::cerr << "\nErreur : " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
