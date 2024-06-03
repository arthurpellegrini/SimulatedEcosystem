#include "Sheep.h"

const int Sheep::satiety = 5;
const int Sheep::lifespan = 50;
const int Sheep::fov = 1;

Sheep::Sheep(Gender gender) : Animal(gender) {
    _satiety = satiety;
}

std::string Sheep::display() const {
    return "S";
}

void Sheep::eat() {
    _satiety = satiety;
}

void Sheep::move() {}

void Sheep::breed() {}

void Sheep::die() {}

int Sheep::getSatiety() {
    return satiety;
}

int Sheep::getLifespan() {
    return lifespan;
}
