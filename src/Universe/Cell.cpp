#include "Cell.h"
#include "../NaturalElement/Grass.h"

Cell::Cell(const vector<int>& position) :
    _isEmpty(true),
    _position(position),
    _animalOnCell(nullptr),
    _naturalElementOnCell(make_unique<Grass>())
{
 updateIsEmpty();
}

void Cell::addAnimal(unique_ptr<Animal> animal) {
 _animalOnCell = move(animal);
 updateIsEmpty();
}

void Cell::removeAnimal() {
 _animalOnCell.reset();
 updateIsEmpty();
}

void Cell::addNaturalElement(unique_ptr<NaturalElement> naturalElement) {
 _naturalElementOnCell = move(naturalElement);
 updateIsEmpty();
}

void Cell::removeNaturalElement() {
 _naturalElementOnCell.reset();
 updateIsEmpty();
}

void Cell::updateIsEmpty() {
 _isEmpty = (!_animalOnCell && !_naturalElementOnCell);
}

bool Cell::isEmpty() const {
 return _isEmpty;
}

vector<int> Cell::getPosition() const {
 return _position;
}

Animal* Cell::getAnimal() const {
 return _animalOnCell.get();
}

NaturalElement* Cell::getNaturalElement() const {
 return _naturalElementOnCell.get();
}

ostream& operator<<(ostream& os, const Cell& s) {
 if (s._animalOnCell) {
  os << s._animalOnCell->display();
 }
 if (s._naturalElementOnCell) {
  os << s._naturalElementOnCell->display();
 }
 return os;
}
