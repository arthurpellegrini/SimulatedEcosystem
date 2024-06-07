#include "Wolf.h"

const int Wolf::_maxSatiety = 10;
const int Wolf::_lifespan = 60;
const int Wolf::_adultAge = 5;
const int Wolf::_cooldown = 3;

Wolf::Wolf(const Gender gender)
    : Animal(gender, _adultAge, _lifespan, _maxSatiety, _cooldown) {}
Wolf::Wolf(const Gender gender, const int age, const int satiety)
    : Animal(gender, age, _adultAge, _lifespan, satiety, _maxSatiety, _cooldown) {}

string Wolf::display() const {
    return "W";
}
