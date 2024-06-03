#include "Cell.h"
#include "../NaturalElement/Grass.h"


Cell::Cell(const vector<int>& position) :
    _isEmpty(true),
    _position(position),
    _animal(nullptr),
    _natural_element(make_unique<Grass>())
{
    updateIsEmpty();
}

void Cell::addAnimal(unique_ptr<Animal> animal) {
    _animal = move(animal);
    updateIsEmpty();
}

void Cell::removeAnimal() {
    _animal.reset();
    updateIsEmpty();
}

void Cell::addNaturalElement(unique_ptr<NaturalElement> naturalElement) {
    _natural_element = move(naturalElement);
    updateIsEmpty();
}

void Cell::removeNaturalElement() {
    _natural_element.reset();
    updateIsEmpty();
}

void Cell::updateIsEmpty() {
    _isEmpty = (!_animal && !_natural_element);
}

bool Cell::isEmpty() const {
    return _isEmpty;
}

vector<int> Cell::getPosition() const {
    return _position;
}

Animal* Cell::getAnimal() const {
    return _animal.get();
}

NaturalElement* Cell::getNaturalElement() const {
    return _natural_element.get();
}

ostream& operator<<(ostream& os, const Cell& cell) {
    if (cell._animal) {
        os << cell._animal->display();
    } else if (cell._natural_element) {
        os << cell._natural_element->display();
    } else {
        os << " ";
    }
    return os;
}
