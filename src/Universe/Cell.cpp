#include "Cell.h"
#include "../NaturalElement/Grass.h"

Cell::Cell(const std::vector<int>& position) :
    _isEmpty(true),
    _position(position),
    _animalOnCell(nullptr),
    _naturalElementOnCell(std::make_unique<Grass>())
{
 updateIsEmpty();
}

void Cell::addAnimal(std::unique_ptr<Animal> animal) {
 _animalOnCell = std::move(animal);
 updateIsEmpty();
}

void Cell::removeAnimal() {
 _animalOnCell.reset();
 updateIsEmpty();
}

void Cell::addNaturalElement(std::unique_ptr<NaturalElement> naturalElement) {
 _naturalElementOnCell = std::move(naturalElement);
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

std::vector<int> Cell::getPosition() const {
 return _position;
}

Animal* Cell::getAnimal() const {
 return _animalOnCell.get();
}

NaturalElement* Cell::getNaturalElement() const {
 return _naturalElementOnCell.get();
}

std::ostream& operator<<(std::ostream& os, const Cell& s) {
 if (s._animalOnCell) {
  os << s._animalOnCell->display();
 }
 if (s._naturalElementOnCell) {
  os << s._naturalElementOnCell->display();
 }
 return os;
}
