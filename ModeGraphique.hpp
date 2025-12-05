#ifndef MODEGRAPHIQUE_HPP
#define MODEGRAPHIQUE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp> 
#include "Grille.hpp"

class ModeGraphique {
private:
    sf::Time vitesseSimulation_; //Temps entre 2 itérations (vitesse de la simulation)
    sf::Clock horloge_; //Définition de l'horloge pour gérer le timing 
    //Définition des composants SFML
    sf::RenderWindow window_; //Pour la fenêtre principale
    sf::RectangleShape cellShape_;

    //On se réfère à la grille du jeu pour prendre les données à afficher 
    const Grille& grille_; 

    //On va se référer à la grille du jeu pour prendre les données à afficher 
    float cellSize_; //Taille en pixels d'une cellule
    void processEvents(); //Fonction pour gérer les évènements que l'on va définir
    void dessiner(); //Fonction qui va dessiner l'état actuel de la grille dans la fenètre 
    //Calcule la génération suivante et mets à jour le temps de la simulation 
    void update(float delta_t, Grille& grille); //delta_t est notre variation du temps (c.a.d le temps écoulé)

public:
    ModeGraphique(const Grille& grille, float vitesseCible = 10.0f);    
    void run(Grille& grille); //démarrer la vitesse principale 
};

#endif
