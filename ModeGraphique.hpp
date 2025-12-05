#ifndef MODEGRAPHIQUE_HPP
#define MODEGRAPHIQUE_HPP

#include "Grille.hpp"

class ModeGraphique {
private:
    float vitesseCible_;
    float horloge_;
    
public:
    ModeGraphique(const Grille& grille, float vitesseCible = 10.0f);
    
    void update(float deltaT, Grille& grille);
    void dessiner(Grille& grille);
    void run(Grille& grille);
};

#endif
