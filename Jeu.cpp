#include "Jeu.hpp"
#include <iostream>
#include <limits>//Pour gérer les erreurs
#include <sstream>// Pour std::stringstream
#include <iomanip>// Pour std::setw, std::setfill
#include <string> // Pour std::string et std::getline
#include <stdexcept>// Pour la gestion des exceptions (try/catch)
#include <filesystem>

// ----------------------------------------------------------------------
// GESTION DU SYSTÈME DE FICHIERS (DÉPLACÉ HORS DE LANCERJEU)
// ----------------------------------------------------------------------

namespace fs = std::filesystem; // Alias pour le système de fichiers

// Fonction statique pour vérifier et créer le dossier 'sortie/'
static void preparerDossierSortie(const std::string& nomDossier) {
    if (!fs::exists(nomDossier)) {
        try {
            if (fs::create_directory(nomDossier)) {
                std::cout << "Préparation : Dossier '" << nomDossier << "' créé." << std::endl;
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Erreur Système de Fichiers: Impossible de créer le dossier '" << nomDossier << "'. " << e.what() << std::endl;
        }
    }
}

// ----------------------------------------------------------------------
// CONSTRUCTEUR ET MODES D'EXÉCUTION
// ----------------------------------------------------------------------

Jeu::Jeu(const std::string& nomFichierEntree): nomFichierEntree_(nomFichierEntree)
{
    //Chargeons la grille avec le motif initial
    grille_.chargerMotif(nomFichierEntree);
}

void Jeu::executerModeConsole(int maxIterations){
    // Créer le dossier de sortie avec le format <nom_fichier>_out
    std::string nomDossierSortie = nomFichierEntree_;
    // Supprimer l'extension du fichier
    size_t lastDot = nomDossierSortie.find_last_of('.');
    if (lastDot != std::string::npos) {
        nomDossierSortie = nomDossierSortie.substr(0, lastDot);
    }
    nomDossierSortie += "_out";
    
    // Créer le dossier s'il n'existe pas
    preparerDossierSortie(nomDossierSortie);
    
    ModeConsole exportateur(nomFichierEntree_, nomDossierSortie); 
    for (int i=0; i<maxIterations; ++i){
        exportateur.expEtatGrille(grille_, i);
        if (i<maxIterations-1){
            grille_.genSuivante();
        }
    }
    std::cout <<"Exportation des " <<maxIterations<< " étapes terminée dans " << nomDossierSortie << "/"<<std::endl;
}

void Jeu::executerModeGraphique(){
    const float FPS_CIBLE = 5.0f;
    ModeGraphique modeGraphique(grille_, FPS_CIBLE);
    modeGraphique.run(grille_);
}

// ----------------------------------------------------------------------
// FONCTIONS DE TEST STATIQUES
// ----------------------------------------------------------------------

static bool comparerGrille(const Grille& grilleActuelle, const Grille& grilleAttendue){
    if (grilleActuelle.getLargeur()!=grilleAttendue.getLargeur()|| 
        grilleActuelle.getHauteur() != grilleAttendue.getHauteur()){
        std::cerr <<" Erreur : Dimensions de la grille non correspondantes."<<std::endl; 
        return false; 
    }
    // Comparaison cellule par cellule :
    for (int y = 0; y < grilleActuelle.getHauteur(); ++y) {
        for (int x = 0; x < grilleActuelle.getLargeur(); ++x) { 
            bool estVivanteActuelle = grilleActuelle.getCellule(x, y)->estVivante();
            bool estVivanteAttendue = grilleAttendue.getCellule(x, y)->estVivante();
            if (estVivanteActuelle != estVivanteAttendue) {
                std::cerr << "Erreur à la cellule (" << x << ", " << y << "). "
                << "Attendu: " << (estVivanteAttendue ? "Vivante" : "Morte")
                << ", Obtenu: " << (estVivanteActuelle ? "Vivante" : "Morte")
                << std::endl;
                return false;
            }
        }
    }
    return true; // Les grilles correspondent
}

static bool verifierEtat(const std::string& nomFichierMotif, const std::string& nomFichierAttendu,int iterations) {
    Grille grilleActuelle(1, 1); 
    Grille grilleAttendue(1, 1);
    try {
        grilleActuelle.chargerMotif(nomFichierMotif);
        for (int i = 0; i < iterations; ++i) {
           grilleActuelle.genSuivante();
        }
        grilleAttendue.chargerMotif(nomFichierAttendu);
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors du chargement ou de la simulation : " << e.what() << std::endl;
        return false;
    }
    return comparerGrille(grilleActuelle, grilleAttendue);
}

// ----------------------------------------------------------------------
// FONCTION D'ENTRÉE ET DE VÉRIFICATION
// ----------------------------------------------------------------------
void lancerVerificationSortie(const std::string& nomFichierInitial){
    std::string fichierAttendu;
    int iterationsAComparer;
    
    std::cout<< "\n========================================" << std::endl;
    std::cout<< "      Validation des Fichiers Sortie" << std::endl;
    std::cout<< "========================================" << std::endl;

    std::cout<<" Entrez le numéro de l'itération à vérifier : ";
    //Gestion des erreurs 
    while (!(std::cin >> iterationsAComparer) || iterationsAComparer < 1) { 
        std::cerr << "Erreur : L'itération doit être un nombre positif : ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //On nettoie le buffer juste après
    std::cout << "Entrez le nom du fichier attendu pour l'état i=" << iterationsAComparer << " (chemin complet ou relatif) :\n";
    std::getline(std::cin, fichierAttendu);
    
    std::cout<< "\n  Début de la vérification  "<<std::endl;
    if (verifierEtat(nomFichierInitial, fichierAttendu, iterationsAComparer)) { // On simule iterationAComparer pas.
        std::cout << "\n RÉSULTAT DU TEST : SUCCÈS !" << std::endl;
    } else {
        std::cout << "\n RÉSULTAT DU TEST : ÉCHEC." << std::endl;
    }
}

void Jeu::lancerJeu(int maxIterations){
    const std::string nomDossierSortie = "sortie";
    
    // Appel de la fonction statique déplacée
    preparerDossierSortie(nomDossierSortie); 

    // Choix du mode :
    std::cout<< " Selectionnez le mode d'exécution \n";
    std::cout<< " 1. Mode Console : \n";
    std::cout<< " 2. Mode Graphique : \n";
    std::cout<< " Entrez 1 ou 2 : \n";
    int choixMode; 

    // Pour gérer les erreurs de saisie :
    while (!(std::cin >> choixMode) || (choixMode < 1 || choixMode >2)){
        std::cout<< "Saisie invalide. Choisissez bien entre 1 ou 2 "<<std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Exécution du mode choisi :
    if (choixMode == 1){
        std::cout<< " Lancement Mode Console...\n";
        this->executerModeConsole(maxIterations);

        // lancerVerificationSortie(nomFichierEntree_); // Fonction pour le test (commentée)
    }else if(choixMode ==2){
        std::cout<<" Lancement Mode Graphique...\n";
        this->executerModeGraphique();
    }
}

