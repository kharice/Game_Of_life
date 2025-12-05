#include "ModeGraphique.hpp"
#include <iostream>

ModeGraphique::ModeGraphique(const Grille& grille, float vitesseCible)
    : vitesseCible_(vitesseCible), horloge_(0.0f) {
}

void ModeGraphique::update(float deltaT, Grille& grille) {
    horloge_ += deltaT;
    
    if (horloge_ >= 1.0f / vitesseCible_) {
        grille.genSuivante();
        horloge_ = 0.0f;
    }
}

void ModeGraphique::dessiner(Grille& grille) {
    // Mode graphique non implémenté
}

void ModeGraphique::run(Grille& grille) {
    std::cout << "Mode graphique non implémenté - SFML non disponible." << std::endl;
}
