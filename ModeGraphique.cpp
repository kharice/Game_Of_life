#include "ModeGraphique.hpp"
#include "cellule.hpp"
#include "Grille.hpp"
#include <iostream>
#include <chrono>
#include <thread>

ModeGraphique::ModeGraphique(const Grille& grille, float v_cible) 
: grille_(grille)
{
    // Utiliser la taille réelle de la grille chargée
    unsigned int grid_height = grille.getHauteur();
    unsigned int grid_width = grille.getLargeur();
    const unsigned int CELL_SIZE = 10; // Chaque cellule fait 10x10 pixels
    
    unsigned int window_width = grid_width * CELL_SIZE;
    unsigned int window_height = grid_height * CELL_SIZE;
    
    // Créer la fenêtre
    window_.create(sf::VideoMode(window_width, window_height), "Jeu de la Vie");
    window_.setPosition(sf::Vector2i(100, 100));
    
    // Calculer la durée cible entre chaque itération (1/v_cible)
    timePerFrame_ = sf::seconds(1.0f/v_cible);
    
    // Initialiser le modèle de cellule avec la bonne taille
    cellShape_.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    cellShape_.setFillColor(sf::Color::White);
}

void ModeGraphique::processEvents(){
    sf::Event event;
    while (window_.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window_.close();
        }       
    }
}

void ModeGraphique::update(float delta_t, Grille& grille){
    //On appelle la méthode de la grille pour la prochain itération
    grille.genSuivante();
}

void ModeGraphique::dessiner(){
    const unsigned int CELL_SIZE = 10;
    
    window_.clear(sf::Color::Black); // Fond noir
    
    // Afficher les cellules vivantes en blanc
    for (int y = 0; y < grille_.getHauteur(); ++y) {
        for (int x = 0; x < grille_.getLargeur(); ++x) {
            const cellule* cell = grille_.getCellule(x, y);
            if (cell && cell->estVivante()) {
                cellShape_.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                window_.draw(cellShape_);
            }
        }
    }
    
    window_.display(); // Rafraîchir l'affichage
}

void ModeGraphique::run(Grille& grille){
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window_.isOpen()){
        processEvents(); //C'est à dire que l'on exécute tous les évènements prévus tant que la fenêtre est ouverte

        //Pour éviter l'accumulation du temps écoulé 
        timeSinceLastUpdate += clock_.restart();

        //Mise à jour de la simulation 
        while(timeSinceLastUpdate >= timePerFrame_){
            timeSinceLastUpdate -= timePerFrame_;
            //On mets à jour aussi le calcul de la génération suivante 
            //On va aussi passer la grille en argument de la fonction pour qu'elle puisse être modifiée
            update(timePerFrame_.asSeconds(), grille);
        }
        dessiner(); //On affiche alors le rendu
    }
}