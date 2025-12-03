//Gestion du jeu 
#ifndef JEU_HPP
#define JEU_HPP

#include <string>
#include <stdexcept>

#include "Grille.hpp"
#include "ModeConsole.hpp"
#include "ModeGraphique.hpp"

class Jeu{
private :
    Grille grille_;  //Instance de la grille du jeu 
    std::string nomFichierEntree_; 
public : 
    //Constructeur du jeu qui va initialiser le jeu en chargeant le motif 
    //NomFichierEntree : chemin du fichier qui contient l'état initial 
    Jeu(const std::string& nomFichierEntree);

    //On interdie la copie vu qu'on utilise des pointeurs ici 
    Jeu(const Jeu&) = delete;
    Jeu& operator = (const Jeu&) = delete;

    void executerModeConsole(int maxIterations); //Fonction pour exécuter le jeu en mode console 
    //maxIterations : nombre max d'itérations que l'on aura défini 
    void executerModeGraphique();

    //Méthode pour obtenir la grille pour les tests unitaires
    const Grille& getGrille() const {return grille_;}

};
#endif