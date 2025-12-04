#include <iostream>
#include <string>
#include <limits> 
#include <stdexcept> //Pour la gestion des erreurs 

#include "Jeu.hpp"

//Fonction pour vider le buffer 
void viderBuffer(){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main (int argc, char* argv[]){
    //Vérification du fichier d'entrée 
    if (argc !=2){
        std::cerr<<"Utilisation: " <<argv[0]<<"<nom_du_fichier_dentree.txt>" << std::endl;
        return 1;
    }
    std::string nomFichierEntree =argv[1];

    int iterations = 0; 

    
    //L'utilisateur va donc maintenant saisir le nombre d'itérations
    std::cout<< "Entrez le nombre d'itérations à effectuer (attention au i-1):";
    if (!(std::cin>>iterations)|| iterations <0){
        std::cerr<<"Saisissez une valeur valide"<<std::endl;
        viderBuffer();
    }
    viderBuffer();
    
    //Lancement de la simulation 
    try{
        Jeu jeu (nomFichierEntree);
        std::cout<<"\n---- Début de la simulation ---" <<std::endl;

        jeu.lancerJeu(iterations); // On lance le jeu 

        std::cout<<"\n---- Fin de la simulation ---" <<std::endl;
    } catch (const std::runtime_error& e){
        //Si il y a une erreur critique 
        std::cerr<<"\n ERREUR CRITIQUE !"<<e.what()<<std::endl;
        return 1;
    }
    return 0;
}