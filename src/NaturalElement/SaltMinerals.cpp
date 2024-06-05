#include "SaltMinerals.h"


const int SaltMinerals::_lifespan = 1;

SaltMinerals::SaltMinerals() : _age(0) {}

string SaltMinerals::display() const {
    return "*";
}

void SaltMinerals::incrementAge() {
    _age++;
}

bool SaltMinerals::shouldTransform() const {
    return _age >= _lifespan;
}
