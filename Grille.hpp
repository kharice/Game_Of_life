#ifndef GRILLE_HPP
#define GRILLE_HPP

#include <vector>
#include <string>
#include "cellule.hpp"

// Classe qui représente toute la grille 
// Elle contient toutes les cellules et gère leur évolution.
class Grille {
private:
    int largeur_;   // largeur de la grille (en nombre de cellules)
    int hauteur_;   // hauteur de la grille
    std::vector<std::vector<cellule*>> tableauCellules_; // matrice de pointeurs vers les cellules
    
    // Fonction qui compte combien de voisins vivants il y a autour d’une cellule
    // (important pour appliquer les règles)
    int comptVoisinsVivants(int x, int y) const;

    // Fonction qui libère toute la mémoire de la grille (appelée dans le destructeur)
    void nettoyerGrille();

    // Initialise une grille vide avec que des cellules mortes (utilisée plusieurs fois)
    void initGrilleVide();

    // Copie toutes les cellules depuis une autre grille (utilisé dans le constructeur de copie)
    void copierDepuis(const Grille& autre);

public:
    // Constructeur par défaut : crée une grille vide
    Grille();

    // Constructeur avec dimensions (pratique si on veut créer une grille fixe)
    Grille(int largeur, int hauteur);

    // Destructeur : on libère toute la mémoire des cellules
    ~Grille();
    
    // Constructeur de copie : permet de créer une nouvelle grille identique à une autre
    Grille(const Grille& autre);

    // Opérateur = : pareil que le constructeur de copie mais pour affectation
    Grille& operator=(const Grille& autre);

    // Charge un motif depuis un fichier texte (les .txt fournis)
    void chargerMotif(const std::string& nomFichier);

    // Génère l'état suivant de la grille 
    void genSuivante();

    // Sauvegarde l’état actuel dans un fichier 
    void sauvegarder(const std::string& nomFichier) const;
    
    // Getters 
    int getLargeur() const { return largeur_; }
    int getHauteur() const { return hauteur_; }

    // Permet de récupérer une cellule de la grille (sans la modifier)
    const cellule* getCellule(int x, int y) const;
    
    // Compare deux grilles pour savoir si elles sont exactement identiques
    // Pour détecter les états stables
    bool estIdentique(const Grille& autre) const;
};

#endif
