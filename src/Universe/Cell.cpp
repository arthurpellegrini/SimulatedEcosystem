#include "Cell.h"

#include "../NaturalElement/Grass.h"

Cell::Cell(const vector<int> &position) : _position(position) {
 this->_isEmpty = false;
 this->_naturalElementOnCell = new Grass();
 this->_animalOnCell = nullptr;
}

void Cell::addAnimal(Animal *animal) {
 this->_animalOnCell = animal;
 this->updateIsEmpty();
}

void Cell::addNaturalElement(NaturalElement *NaturalElement) {
 this->_naturalElementOnCell = NaturalElement;
 this->updateIsEmpty();
}

void Cell::updateIsEmpty() {
 if (this->_animalOnCell == nullptr && this->_naturalElementOnCell == nullptr) {
  this->_isEmpty = true;
 } else {
  this->_isEmpty = false;
 }
}

bool Cell::isEmpty() {
 return this->_isEmpty;
}

void Cell::setIsEmpty(const bool value) {
     this->_isEmpty = value;
}

ostream &operator <<(ostream &os, const Cell &s) {
 if (s._animalOnCell != nullptr) {
  os << s._animalOnCell->display();
 }
 if (s._naturalElementOnCell != nullptr) {
  os << s._naturalElementOnCell->display();
 }
 return (os);
}
