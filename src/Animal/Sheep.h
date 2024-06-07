#ifndef SHEEP_H
#define SHEEP_H

#include "Animal.h"


class Sheep : public Animal {
public:
    explicit Sheep(Gender gender);
    Sheep(Gender gender, int age, int satiety);

    string display() const override;

private:
    static const int _adultAge;
    static const int _lifespan;
    static const int _cooldown;
    static const int _maxSatiety;
    static const int _fov;
};

#endif // SHEEP_H
