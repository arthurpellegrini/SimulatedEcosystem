#include "SaltMinerals.h"


SaltMinerals::SaltMinerals() : _age(0) {}

string SaltMinerals::display() const {
    return "M";
}

void SaltMinerals::incrementAge() {
    _age++;
}

bool SaltMinerals::shouldTransform() const {
    return _age >= _lifespan;
}
