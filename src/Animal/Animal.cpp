#include "Animal.h"

const int Animal::_maxSatiety = 25;

Animal::Animal(Gender gender) : _age(0), _gender(gender), _satiety(_maxSatiety) {}

int Animal::getAge() const {
 return _age;
}

Gender Animal::getGender() const {
 return _gender;
}

int Animal::getSatiety() const {
 return _satiety;
}

void Animal::increaseAge() {
 _age++;
}

void Animal::resetSatiety(int value) {
 _satiety = value;
}

void Animal::decreaseSatiety() {
 if (_satiety > 0) {
  _satiety--;
 }
}

Animal::~Animal() {}

string Animal::display() const {
 return "A";
}

ostream& operator<<(ostream &os, const Animal &animal) {
 return os << animal.display();
}
