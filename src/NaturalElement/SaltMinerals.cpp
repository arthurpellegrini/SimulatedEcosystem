#include "SaltMinerals.h"


const int SaltMinerals::_lifespan = 1;

SaltMinerals::SaltMinerals() : _age(0) {}

void SaltMinerals::incrementAge() {
    _age++;
}

bool SaltMinerals::shouldTransform() const {
    return _age >= _lifespan;
}

string SaltMinerals::display() const {
    return "*";
}
