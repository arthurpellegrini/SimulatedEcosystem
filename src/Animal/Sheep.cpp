#include "Sheep.h"


const int Sheep::_maxSatiety = 5;
const int Sheep::_lifespan = 50;
const int Sheep::_fov = 1;


Sheep::Sheep(Gender gender) : Animal(gender) {
    _satiety = _maxSatiety;
}

string Sheep::display() const {
    return "S";
}

void Sheep::eat() {
    _satiety = _maxSatiety;
}

void Sheep::move() {
    // Logic for moving within the field of view
}

void Sheep::breed() {
    // Logic for breeding
}

void Sheep::die() {
    // Logic for dying
}

int Sheep::getLifespan() {
    return _lifespan;
}
