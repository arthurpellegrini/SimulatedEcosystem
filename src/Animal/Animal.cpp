#include "Animal.h"

Animal::Animal(Gender gender, int maxSatiety, int lifespan)
    : _age(0), _gender(gender), _satiety(maxSatiety), _maxSatiety(maxSatiety), _lifespan(lifespan) {}
Animal::Animal(Gender gender, int maxSatiety, int lifespan, int age, int satiety)
    : _age(age), _gender(gender), _satiety(satiety), _maxSatiety(maxSatiety), _lifespan(lifespan) {}

Animal::~Animal() {}

void Animal::increaseAge() { _age++; }
bool Animal::isDead() const { return _satiety <= 0 || _age >= _lifespan; }

void Animal::eat() { _satiety = _maxSatiety; }
void Animal::decreaseSatiety() { _satiety--; }

bool Animal::canBreed(const Animal &animal) const { return this->_gender != animal.getGender(); }


int Animal::getAge() const { return _age; }
Gender Animal::getGender() const { return _gender; }
int Animal::getSatiety() const { return _satiety; }

ostream& operator<<(ostream &os, const Animal &animal) {
    return os << animal.display();
}