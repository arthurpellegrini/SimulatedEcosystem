/**
 * Project Untitled
 */


#include "Universe.h"

/**
 * Universe implementation
 */
Universe::Universe(std::vector<int> dimensions) : dimensions(dimensions) {
 // Initialisation du tableau
 //

 field.resize(dimensions[0]);
 for (int i = 0; i < dimensions[0]; i++) {
  field[i].resize(dimensions[1]);
 }

 // Remplir le tableau avec des valeurs (par exemple, des valeurs incrémentales)
 for (int i = 0; i < dimensions[0]; i++) {
  for (int j = 0; j < dimensions[1]; j++) {
   //field[i][j] = Case({i,j});
  }
 }
}


/**
 * @return void
 */
void Universe::nextGeneration() {
    return;
}

/**
 * @param cell
 * @return Cell []

Cell [] Universe::neighborhood(Cell cell) {
    return null;
}*/


std::vector<std::vector<Cell>>& Universe::getField() {
 return field;
}

bool Universe::getisDead() {
 return isDied;
}

void Universe::setisDead(bool isDead)  {
 isDied = isDead;// faut rename
}

