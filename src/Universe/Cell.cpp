#include "Cell.h"


#include "../Animal/Sheep.h"
#include "../Animal/Wolf.h"
#include "../NaturalElement/Grass.h"
#include "../NaturalElement/SaltMinerals.h"


Cell::Cell(const vector<int>& position) :
    _isEmpty(true),
    _position(position),
    _animal(nullptr),
    _natural_element(nullptr)
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

bool Cell::hasAnimal() const {
    return _animal!=nullptr;
}

bool Cell::hasSheep() const {
    return hasAnimal() && dynamic_cast<Sheep*>(_animal.get())!=nullptr;
}

bool Cell::hasWolf() const {
    return hasAnimal() && dynamic_cast<Wolf*>(_animal.get())!=nullptr;
}

bool Cell::hasNaturalElement() const {
    return _natural_element!=nullptr;
}

bool Cell::hasGrass() const {
    return hasNaturalElement() && dynamic_cast<Grass*>(_natural_element.get())!=nullptr;
}

bool Cell::hasSaltMinerals() const {
    return hasNaturalElement() && dynamic_cast<SaltMinerals*>(_natural_element.get())!=nullptr;
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

string Cell::display() const {
    string output;
    if (this->_animal) {
        output = this->_animal->display();
    } else {
        output = " ";
    }
    if (this->_natural_element) {
        output += this->_natural_element->display();
    } else {
        output += " ";
    }
    return output;
}

ostream& operator<<(ostream &os, const Cell& cell) {
    return os << cell.display();
}
