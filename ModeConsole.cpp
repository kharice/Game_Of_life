
#include <iomanip>
#include "ModeConsole.hpp"
#include "cellule.hpp"
ModeConsole::ModeConsole(const std::string& nomFichierEntree){
    //Tout d'abordd extrayons la base du nom du chier (sans l'extension)
    size_t lastDot = nomFichierEntree.find_last_of('.'); 
    nomBaseFichier_ = nomFichierEntree.substr(0, lastDot);
    //Définissons le nom du dossier du dossier 
    nomDossierSortie_ = nomBaseFichier_ + "_out";
    //On créé alors enfin le dossier de sortie
    creerDossierSortie();
}
void ModeConsole::expEtatGrille(const Grille& grille, int iteration) const{
    //Construisons les noms de fichiers 
    std::stringstream ss;
    ss <<nomDossierSortie_ <<"/" <<nomBaseFichier_ << "_iteration";
    //Formatons l'indice des itérations sur 2 chiffres avec des 0 de tête 
    ss <<std::setw(2) <<std::setfill('0') <<iteration;
    ss << ".txt";

    std::string cheminFichier =ss.str();
    //Ouverture du fichier de sortie 
    std::ofstream fichierSortie(cheminFichier);
    if (!fichierSortie.is_open()){ //On vérifie que le fichier est bien ouvert 
        throw std::runtime_error("Impossible d'ouvrire le fichier !");
    }
    //Nous allons maintenant remplir le fichier : 
    //Pour écrire les dimensions 
    fichierSortie <<grille.getLargeur() <<" "<< grille.getHauteur() << "\n";
    //Pour écrire l'état des cellules
    int hauteur = grille.getHauteur(); //On récupère la hauteur à l'aide de la classe Grille
    int largeur = grille.getLargeur(); //On récupère la largeur à l'aide de la classe Grille aussi 

    for (int y=0; y<hauteur; ++y){
        for (int x=0; x<largeur; ++x){
            //On va utiliser le getter défini dans Grille pour avoir accès à la cellule 
            const cellule* cell = grille.getCellule(x,y);
            //Condition pour écrire "1" si la cellule est vivante sinon "0" si la cellule est morte
            if (cell && cell -> estVivante()){
                fichierSortie <<'1';
            }else{
                fichierSortie <<'0';
            }
        }
        fichierSortie <<"\n"; //Juste pour sauter une ligne après chaque rangée pour que ce soit plus lisible 
    }
    //On ferme enfin le fichier 
    fichierSortie.close();
} 