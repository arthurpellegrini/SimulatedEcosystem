#include "Animal.h"


Animal::Animal(const Gender gender, const int maxSatiety, const int lifespan, const int age, const int satiety)
    : _age(age), _satiety(satiety), _maxSatiety(maxSatiety), _lifespan(lifespan), _gender(gender) {}

Animal::Animal(const Gender gender, const int maxSatiety, const int lifespan)
    : Animal(gender, maxSatiety, lifespan, 0, maxSatiety) {}

Animal::~Animal() = default;

void Animal::move()
{
    _canMove = false;
}
bool Animal::canMove() const
{
    return _canMove;
}
void Animal::resetCanMove()
{
    _canMove = true;
}


void Animal::increaseAge()
{
    _age++;
}
bool Animal::isOldAgeDead() const
{
    return _age >= _lifespan;
}
bool Animal::isHungerDead() const
{
    return _satiety <= 0;
}

void Animal::eat()
{
    _satiety = _maxSatiety;
}
void Animal::decreaseSatiety()
{
    _satiety--;
}

int Animal::getAge() const { return _age; }
int Animal::getSatiety() const { return _satiety; }
Gender Animal::getGender() const { return _gender; }

ostream& operator<<(ostream &os, const Animal &animal) {
    return os << animal.display();
}