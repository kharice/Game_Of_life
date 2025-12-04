//Classe pour la gestion de la grille
#ifndef GRILLE_HPP
#define GRILLE_HPP
#include <vector> //Pour utiliser des vecteurs (pour les tableaux dynamiques)
#include <stdexcept> //Pour gérer les erreurs 
#include <string> //Pour gérer le nom du fichier 
#include <sstream> //Pour lire la première ligne du fichier 

#include "cellule.hpp"
#include "EtatCellule.hpp"
#include "Rules.hpp"

class Grille{
private : 
    int largeur_ = 0;
    int hauteur_ = 0;

    //On va faire un tableau avec des cases et chaque case va contenir une cellule
    //Ce sera une matrice de pointeurs vers les cellules 
    std::vector<std::vector<cellule*>> tableauCellules_;
    void initGrilleVide(); 
    int comptVoisinsVivants(int x, int y) const; //Compte le nombre de voisins vivants d'une cellule
    //x : coordonnée X de la cellule centrale
    //y : coordonnée Y de la cellule centrale
    void nettoyerGrille(); //Fonction pour libérer la mémoire allouée à toutes les cellules de la grille 
public : 
    Grille() = default; //Constructeur pour créer la grille avec comme taille par défaut (0,0)
    Grille(int largeur, int hauteur);
    ~Grille(); //Destructeur 
    // Interdire la copie (car la gestion des pointeurs est complexe)
    Grille(const Grille&) = delete;
    Grille& operator=(const Grille&) = delete;

    void chargerMotif(const std::string& nomFichier); //On va charger l'état initial de la grille à partir du fichier texte 

    
    void genSuivante(); //Fonction générant la prochaine génération 

    //Getters pour les dimensions de la grilles
    int getLargeur() const{return largeur_;}
    int getHauteur() const{return hauteur_;}
    const cellule* getCellule(int x, int y) const; 
};
#endif 