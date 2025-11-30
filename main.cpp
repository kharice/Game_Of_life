//Génération du fichier 
//On sauvegarde chaque étape (itération dans le fichier de sauvegarde)
#include <iostream>
#include <fstream> //Bibliothèque standard pour gérer les fichiers (création et écriture)
#include <string>
#include <filesystem>
#include <stdexcept>

//I - Génération fichier texte 
std::ofstream fichier_sortie ("fichier.txt"); //Si le fichier existe déjà il sera alors écrasé 
//Vérifions si le fichier s'est bien ouvert : 
if (fichier_sortie.is_opent()){
    //fichier prêt à être écrit 
    std::cout<<"Le fichier est prêt à être écrit"<<std::endl;
}else{
    //Echec de l'ouverture 
    std::cout<<"Echec de l'ouverture du fichier"<<
}

//On va alors écrire dans le fichier 
fichier_sortie <<"Ceci est la première ligne du fichier"<< std::endl;
fichier_sortie <<"Ceci est la deuxième ligne."<<std::endl;


// II - Génération dossier de sortie 

//Nous allons utiliser un namespace pour rendre plus facile les appels de la bibliothèque pour le système de fichiers :
namespace fs = std::filesystem;
//Définissons le nom du fichier d'entrée 
std::string nom_fichier_entree = "Nom du fichier.ext"; 
//Chemin d'entrée du fichier 
fs::path chemin_fichier = nom_fichier_entree;
//Nom de base du fichier sans l'extension 
std::string nom_base = nom_fichier_entree.substr(0, nom_fichier_entree.find_last_of("."));
//std::string nom_base chemin_fichier.stem().string();
//Nom du dossier de sortie 
fs::path nom_dossier_sortie = nom_base + "out";
std::cout <<"Nom du dossier cible :"<<nom_dossier_sortie<<std::endl;

//Création du fichier de sortie 
if (fs::create_directory(nom_dossier_sortie)){
    std::cout<<"Dossier cree :" <<nom_dossier_sortie<<std::endl;
}else{
    //Si le dossier est déjà créé 
    if (fs::exists(nom_dossier_sortie)){
        std::cout<<"Le dossier existe deja :"<<nom_dossier_sortie<<std::endl;
    }else {
        //En cas d'erreur :
        std::cerr<<"Impossible de créer le dossier"<<std::endl;
        return 1;
    }
}

//Stockons maintenant les résultats 
//Définition du chemin complet du fichier resultat
fs::path chemin_fichier_resultat = nom_dossier_sortie/"iteration_01.txt";
//Ouverture du flux de sortie dans le chemin 
std::ofstream fichier_resultat(chemin_fichier_resultat);

if(fichier_resultat.is_open()){
    fichier_resultat<<"Resultat de la premiere iteration."<<std::endl;
    fichier_resultat.close();
    std::cout<<"Fichier ecrit dans :"<<chemin_fichier_resultat<<std::endl;
}