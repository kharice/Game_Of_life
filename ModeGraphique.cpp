#include "ModeGraphique.hpp"
#include <iostream>
#include "cellule.hpp"
#include "Grille.hpp"
#include <chrono>
#include <thread>


ModeGraphique::ModeGraphique(const Grille& grille, float vitesseCible)
    : grille_(grille) {
        // Utiliser la taille réelle de la grille chargée
   // --- NOUVELLES DIMENSIONS CIBLES DE LA FENÊTRE ---
    const unsigned int WINDOW_SIZE = 80;
    unsigned int grid_height = grille.getHauteur();
    unsigned int grid_width = grille.getLargeur();
    // 1. Calculer la nouvelle taille de cellule (cellSize_ membre)
    // On prend la dimension la plus petite pour s'assurer que tout rentre.
    // Si la grille est 10x20, la taille de cellule sera 80/20 = 4.
    float cell_width = (float)WINDOW_SIZE / grid_width;
    float cell_height = (float)WINDOW_SIZE / grid_height;

    // Assurer que la cellule est un carré (la contrainte la plus forte l'emporte)
    cellSize_ = std::min(cell_width, cell_height); 
    
    // 2. Créer la fenêtre avec la taille fixe
    window_.create(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Jeu de la Vie (80x80)");
    window_.setPosition(sf::Vector2i(100, 100));
    
    // 3. Calculer la durée cible entre chaque itération
    vitesseSimulation_ = sf::seconds(1.0f/vitesseCible);
    
    // 4. Initialiser le modèle de cellule avec la taille calculée
    cellShape_.setSize(sf::Vector2f(cellSize_, cellSize_));
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
void ModeGraphique::update(float deltaT, Grille& grille) {
    grille.genSuivante(); //On appelle la méthode de la grille pour la prochaine itération 
}

void ModeGraphique::dessiner() {
    window_.clear(sf::Color::Black); // Fond noir
    for (int y = 0; y < grille_.getHauteur(); ++y) {
        for (int x = 0; x < grille_.getLargeur(); ++x) {
            const cellule* cell = grille_.getCellule(x, y);
            if (cell && cell->estVivante()) {
                cellShape_.setPosition(x * cellSize_, y * cellSize_);
                window_.draw(cellShape_);
            }
        }
    }
    window_.display(); // Rafraîchir l'affichage
}

void ModeGraphique::run(Grille& grille) {
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window_.isOpen()){
        processEvents(); //C'est à dire que l'on exécute tous les évènements prévus tant que la fenêtre est ouverte

        //Pour éviter l'accumulation du temps écoulé 
        timeSinceLastUpdate += horloge_.restart();

        //Mise à jour de la simulation 
        while(timeSinceLastUpdate >= vitesseSimulation_){
            timeSinceLastUpdate -= vitesseSimulation_;
            //On mets à jour aussi le calcul de la génération suivante 
            //On va aussi passer la grille en argument de la fonction pour qu'elle puisse être modifiée
            update(vitesseSimulation_.asSeconds(), grille);
        }
        dessiner(); //On affiche alors le rendu
    }
}
