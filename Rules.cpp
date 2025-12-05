#include "Rules.hpp"
#include "EtatCellule.hpp"

cellule* Rules::calculerProchainEtat(const cellule* celluleActuelle, int nbVoisinsVivants) {
    int x = celluleActuelle->getX();
    int y = celluleActuelle->getY();

    if (celluleActuelle->estVivante()) {
        // Cellule vivante : reste vivante si 2 ou 3 voisins vivants
        if (nbVoisinsVivants == 2 || nbVoisinsVivants == 3) {
            return new CelluleVivante(x, y);
        } else {
            return new CelluleMorte(x, y);
        }
    } else {
        // Cellule morte : devient vivante si exactement 3 voisins vivants
        if (nbVoisinsVivants == 3) {
            return new CelluleVivante(x, y);
        } else {
            return new CelluleMorte(x, y);
        }
    }
}
