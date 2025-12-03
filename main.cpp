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

    //Etape pour la saisie du Mode d'utilisation 
    std::string mode;
    std::cout <<"Choisissez le mode d'exécution :"<<std::endl;
    std::cout<<"Entrez 'console' ou 'graphique'";
    std::cin>> mode;

    if (mode=="console"){
        //L'utilisateur va donc maintenant saisir le nombre d'itérations
        std::cout<< "Entrez le nombre d'itérations à effectuer :";
        if (!(std::cin>>iterations)|| iterations <0){
            std::cerr<<"Saisissez une valeur valide"<<std::endl;
            viderBuffer();
        }
    }else if (mode !="graphique"){
        std::cerr << "Mode non reconnu! Le programme va s'arrêter "<<std::endl;
        return 1;
    }
    //Lancement de la simulation 
    try{
        Jeu jeu (nomFichierEntree);
        std::cout<<"\n---- Début de la simulation ---" <<std::endl;
        if (mode =="console"){
            //Lancement de la création des fichiers dans le dossier
            std::cout<<"Execution en mode CONSOLE. Exportation de " <<iterations<<"étapes..."<<std::endl;
            jeu.executerModeConsole(iterations);
            std::cout<<"Exportation terminée avec succès."<<std::endl;
        } else if (mode=="graphique"){
        //Lancement de la fenêtre sfml
        std::cout <<"Execution en mode GRAPHIQUE. " <<std::endl;
        jeu.executerModeGraphique();
        }
    } catch (const std::runtime_error& e){
        //Si il y a une erreur critique 
        std::cerr<<"\n ERREUR CRITIQUE !"<<e.what()<<std::endl;
        return 1;
    }
    return 0;
}