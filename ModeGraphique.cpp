#include "ModeGraphique.hpp"
#include "cellule.hpp"
#include "Grille.hpp"
#include <iostream>

ModeGraphique::ModeGraphique(const Grille& grille, float v_cible) 
: window_(sf::VideoMode(grille.getLargeur()*cellSize_, grille.getHauteur()*cellSize_), "Jeu de la Vie "), grille_(grille)
{
    //On va calculer la durée cible entre chaque itération (1/v_cible)
    timePerFrame_ = sf::seconds(1.0f/v_cible);
    //Initialisons le modèle de cellule 
    cellShape_.setSize(sf::Vector2f(cellSize_, cellSize_));
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
    window_.clear(sf::Color::Black); //La fenêtre aura un fond noir 

    int hauteur = grille_.getHauteur();
    int largeur = grille_.getLargeur();
    
    for (int y =0; y<hauteur, ++y;){
        for (int x=0; x<largeur, ++x;){
            //Accédons à la cellule pour recupérer son état
            const cellule* cell = grille_.getCellule(x,y);
            if (cell && cell-> estVivante()){
                cellShape_.setFillColor(sf::Color::White); //On mets les cellule vivante en blanc 
                //Calcul des coordonnées d'affichage 
                cellShape_.setPosition(x*cellSize_, y*cellSize_);
                //Dessiner la cellule 
                window_.draw(cellShape_);
            }
        }
    }
    window_.display(); //On affiche ce que l'on a créé
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