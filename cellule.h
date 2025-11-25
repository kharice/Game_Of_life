// cellule.h
// Small helper declarations for the Game of Life demo

#ifndef CELLULE_H
#define CELLULE_H

#include <SFML/Graphics.hpp>
#include <vector>

void initializeGrid();
void renderGrid(sf::RenderWindow &window);
void updateGrid();

#endif // CELLULE_H
