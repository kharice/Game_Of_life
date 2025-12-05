#ifndef CELLULE_HPP
#define CELLULE_HPP

class cellule {
public:
    cellule(int x, int y) : x_(x), y_(y) {}
    virtual ~cellule() = default;
    
    virtual bool estVivante() const = 0;
    
    int getX() const { return x_; }
    int getY() const { return y_; }

private:
    int x_, y_;
};

#endif
