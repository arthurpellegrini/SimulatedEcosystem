#include "Sheep.h"


const int Sheep::_maxSatiety = 5;
const int Sheep::_lifespan = 50;


Sheep::Sheep(Gender gender) : Animal(gender, _maxSatiety, _lifespan) {}
Sheep::Sheep(Gender gender, int age, int satiety) : Animal(gender, _maxSatiety, _lifespan, age, satiety) {}

Sheep::Sheep(int age, int satiety, Gender gender) : Animal(age, satiety, gender) {}

string Sheep::display() const {
    return "S";
}
