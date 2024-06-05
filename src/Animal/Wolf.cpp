#include "Wolf.h"


const int Wolf::_maxSatiety = 10;
const int Wolf::_lifespan = 60;


Wolf::Wolf(Gender gender) : Animal(gender, _maxSatiety, _lifespan) {}
Wolf::Wolf(Gender gender, int age, int satiety) : Animal(gender, _maxSatiety, _lifespan, age, satiety) {}


Wolf::Wolf(int age, int satiety, Gender gender) : Animal(age, satiety, gender) {}


string Wolf::display() const {
    return "W";
}


