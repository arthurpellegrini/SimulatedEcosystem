#include "Sheep.h"

const int Sheep::_satiety = 5;
const int Sheep::_lifespan = 50;
const int Sheep::_fov = 1;

Sheep::Sheep(Gender gender) : Animal(gender) {
    _satiety = _satiety;
}

string Sheep::display() const {
    return "S";
}

void Sheep::eat() {
    _satiety = _satiety;
}

void Sheep::move() {}

void Sheep::breed() {}

void Sheep::die() {}

int Sheep::getSatiety() {
    return _satiety;
}

int Sheep::getLifespan() {
    return _lifespan;
}
