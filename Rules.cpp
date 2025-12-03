#include "Rules.hpp"

cellule* Rules::calculerProchainEtat(const cellule*celluleActuelle, int nbVoisinsVivants){
    //Récupérons déjà les données pour construire une nouvelle cellule 
    int x = celluleActuelle -> getX();
    int y = celluleActuelle -> getY();

    if (celluleActuelle->estVivante()){
        //Dans le cas où la cellule actuelle est vivante
        //Règle 1 & Règle 2: Mort par sous population (<2) et Mort par surpopulation (>3)
        if (nbVoisinsVivants <2 || nbVoisinsVivants >3){
            return new CelluleMorte(x,y);
        }else{
            //Règle 3 : La cellule reste vivante (elle a 2 ou trois voisins vivants)
            return new CelluleVivante(x,y);
        }
    }else{
        //Dans le cas où la cellule actuelle est morte 

        //Règle 4 : Naissance d'une cellule (Elle a exactement 3 voisins)
        if (nbVoisinsVivants ==3){
            return new CelluleVivante(x,y); 
        }else{
            //Elle reste morte 
            return new CelluleMorte(x,y);
        }
    }
}