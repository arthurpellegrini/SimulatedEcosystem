#ifndef SHEEP_H
#define SHEEP_H

#include "Animal.h"


class Sheep : public Animal {
public:
    Sheep(Gender gender);
    Sheep(Gender gender, int age, int satiety);

    string display() const override;

private:
    static const int _maxSatiety;
    static const int _lifespan;
};

#endif // SHEEP_H
