#ifndef MODEGRAPHIQUE_HPP
#define MODEGRAPHIQUE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp> // Pour sf::Clock et sf::Time
#include "Grille.hpp"

class ModeGraphique{
private :
    //On va définir nos composants SFML : 
    sf::RenderWindow window_; //Ce sera notre fenêtre principale
    sf::RectangleShape cellShape_; //Pour représenter nos cellules sous forme rectangulaire 
    sf::Clock clock_; //On défini l'horloge qui nous permettra de gérer le timing des itérations 
    sf::Time timePerFrame_; //Définition du temps entre 2 itérations (vitesse de la simulation)

    //On se réfère à la grille du jeu pour prendre les données à afficher 
    const Grille& grille_; 
    //On va maintenant gérer l'affichage :
    const float cellSize_ = 10.0f; //Taille en pixels d'une cellule
    void processEvents(); //Fonction pour gérer les évènements que l'on va définir
    void dessiner(); //Fonction qui va dessiner l'état actuel de la grille dans la fenètre 

    //Calcule la génération suivante et mets à jour le temps de la simulation 
    void update(float delta_t, Grille& grille); //delta_t est notre variation du temps (c.a.d le temps écoulé)
public : 
    ModeGraphique(const Grille& grille, float v_cible =10.0f); //Constructeur pour initialiser la fenêtre et la vitesse de simulation 
    //v_cible : vitesse cible pour la simulation et grille est toujours la grille que l'on doit afficher 

    void run(Grille& grille);//Fonction nous permettant de démarrer la boucle principale pour démarrer la simulation 
};

#endif 