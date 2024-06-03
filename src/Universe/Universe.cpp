/**
 * Project Untitled
 */


#include "Universe.h"

/**
 * Universe implementation
 */
Universe::Universe(const vector<int> &size) {
 this->width = size[0];
 this->height = size[1];

 cells.resize(size[0]);
 for (int i = 0; i < size[0]; i++) {
  cells[i].resize(size[1]);
 }

// Todo : Génération aléatoire des cellules
}

void Universe::nextGeneration() {
    return;
}

vector<vector<Cell>>& Universe::getCells() {
 return this->cells;
}