#include "Wolf.h"

const int Wolf::satiety = 10;
const int Wolf::lifespan = 60;
const int Wolf::fov = 1;

Wolf::Wolf(Gender gender) : Animal(gender) {
    _satiety = satiety;
}

std::string Wolf::display() const {
    return "W";
}

void Wolf::eat() {
    _satiety = satiety;
}

void Wolf::move() {}

void Wolf::breed() {}

void Wolf::die() {}

int Wolf::getSatiety() {
    return satiety;
}

int Wolf::getLifespan() {
    return lifespan;
}
