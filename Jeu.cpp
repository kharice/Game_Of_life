#include "Jeu.hpp"
#include <iostream>

//Nous allons utiliser le constructeur pour initialiser la grille en chargeant l'état intial à partir de notre fichier 
Jeu::Jeu(const std::string& nomFichierEntree): nomFichierEntree_(nomFichierEntree)
{
    //Chargeons la grille avec le motif initial
    grille_.chargerMotif(nomFichierEntree);
}

// Ensuite si on exécute le jeu en mode console 
void Jeu::executerModeConsole(int maxIterations){
    ModeConsole exportateur(nomFichierEntree_); //On créé une instance de ModeConsole pour gérer l'exportation des fichiers
    for (int i=0; i<maxIterations; ++i){
        //Exportation de l'état actuel sachant que l'état initial est i=0
        exportateur.expEtatGrille(grille_, i);
        //Calculons l'état suivant 
        if (i<maxIterations){
            grille_.genSuivante();
        }
    }
    std::cout <<"Exportation  des" <<maxIterations<< "étapes terminée."<<std::endl;
}

void Jeu::executerModeGraphique(){
    //On fixe le taux de rafraichissement cible à 5 itérations par seconde
    const float FPS_CIBLE = 5.0f;
    ModeGraphique modeGraphique(grille_, FPS_CIBLE);//On créé un objet qui va nous permettre de lancer la fenêtre et la boucle du jeu avec une référence à la grille 
    //Lancement de la boucle principale pour que le jeu y reste bloquée jusqu'à ce que la fenêtre soit fermée
    modeGraphique.run(grille_);

}