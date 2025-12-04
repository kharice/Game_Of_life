#include <string> 
#include <fstream> 
#include <sstream>
#include <iomanip> //Pour  les numéros de fichiers avec zéros de tête (pour écrire 01" par ex.)
#include "Grille.hpp"

#ifndef MODECONSOLE_HPP
#define MODECONSOLE_HPP

class ModeConsole{
private:
    std::string nomBaseFichier_; //On prends alors le nom de base du fichier sans l'extension txt
    std::string nomDossierSortie_; //Nom du dossier où on va stocker les fichiers de sortie pour chaque itération 

    //void creerDossierSortie() const; //Création du dossier de sortie si il n'existe pas déjà 
public :
    //Initialise le nom du dossier et tente de le créer
    ModeConsole(const std::string& nomFichierEntree, const std::string& nomDossier); //Constructeur pour exporter la grille
    //Méthode pour exporter l'état actuel de la grille à chaque itération dans des fichiers texte
    void expEtatGrille(const Grille& grille, int iteration) const;
    //itération : indice de l'itération pour que l'on puisse nommer le fichier 
    //On prends "grille" pour pouvoir écrire son état actuel dans le fichier 
};

#endif