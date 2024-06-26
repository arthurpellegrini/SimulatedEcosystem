#include "Sheep.h"

const int Sheep::_maxSatiety = 5;
const int Sheep::_lifespan = 50;
const int Sheep::_adultAge = 4;
const int Sheep::_cooldown = 3;
const int Sheep::_fov = 5;

Sheep::Sheep(const Gender gender)
    : Animal(gender, _adultAge, _lifespan, _maxSatiety, _cooldown) {}
Sheep::Sheep(const Gender gender, const int age, const int satiety)
    : Animal(gender, age, _adultAge, _lifespan, satiety, _maxSatiety, _cooldown) {}

int Sheep::getFOV() { return _fov; }

string Sheep::display() const {
    return "S";
}
