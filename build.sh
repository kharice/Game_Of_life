#!/bin/bash
set -x

# Nom du fichier exécutable à créer
EXECUTABLE="jeu_de_la_vie"

# Nom du fichier d'entrée contenant le motif de la grille
FICHIER_ENTREE="test1.txt" 


# ======================================================================
# --- ÉTAPE 1 : COMPILATION ---
# Utilisation de l'approche standard pour lier SFML 
# On liste simplement les bibliothèques SFML nécessaires.
# ======================================================================

echo " Démarrage de la compilation pour WSL/Ubuntu..."

g++ -std=c++17 \
    main.cpp Jeu.cpp ModeConsole.cpp ModeGraphique.cpp Grille.cpp Rules.cpp \
    -o $EXECUTABLE \
    -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio

# Vérifie si la compilation s'est terminée sans erreur (code de sortie 0)
if [ $? -ne 0 ]; then
    echo " Erreur de compilation "
    exit 1
fi

echo " Compilation réussie ! Exécutable créé : $EXECUTABLE"

# ======================================================================
# --- ÉTAPE 2 : EXÉCUTION ---
# ======================================================================

echo -e "\n Démarrage de l'exécution..."

# Exécute le programme en lui passant le nom du fichier d'entrée en argument
./$EXECUTABLE $FICHIER_ENTREE

echo -e "\nFin de l'exécution du programme."