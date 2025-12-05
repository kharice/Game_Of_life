#ifndef CELLULE_HPP //Si le fichier n'est pas créé
#define CELLULE_HPP //On le défini alors et le compilateur continue la lecture du fichier 

//Classe mère où on va définir nos cellules 
class cellule { 
public:
    cellule(int x, int y) : x_(x), y_(y) {} //Constructeur qui va prendre les coordonnées des cellules 
    virtual ~cellule() = default; //Destructeur pour gérer les pointeurs 
    
    virtual bool estVivante() const = 0; //Méthode virtuelle qui va nous permettre d'identifier l'état de la cellule
    //const : Ne modifie pas les valeurs de x_ ou y_ 
    // =0 : Pour rendre la classe abstraite 
    
    //Getters pour les coordonnées :
    int getX() const { return x_; } 
    int getY() const { return y_; }

private:
    int x_, y_; //Coordonnées de la cellule 
};

#endif
