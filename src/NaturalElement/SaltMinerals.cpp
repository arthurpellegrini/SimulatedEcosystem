#include "SaltMinerals.h"

SaltMinerals::SaltMinerals() : age(0) {}

string SaltMinerals::display() const {
 return "*";
}

void SaltMinerals::incrementAge() {
 age++;
}

bool SaltMinerals::shouldTransform() const {
 return age >= lifespan;
}
