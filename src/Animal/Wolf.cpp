#include "Wolf.h"

const int Wolf::_maxSatiety = 10;
const int Wolf::_lifespan = 60;
const int Wolf::_fov = 1;

Wolf::Wolf(Gender gender) : Animal(gender) {
    _satiety = _maxSatiety;
}

string Wolf::display() const {
    return "W";
}

void Wolf::eat() {
    _satiety = _maxSatiety;
}

void Wolf::move() {}

void Wolf::breed() {}

void Wolf::die() {}

int Wolf::getSatiety() {
    return this->_satiety;
}

int Wolf::getLifespan() {
    return _lifespan;
}
