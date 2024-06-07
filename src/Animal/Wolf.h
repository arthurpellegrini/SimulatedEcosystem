#ifndef WOLF_H
#define WOLF_H

#include "Animal.h"


class Wolf : public Animal {
public:
    explicit Wolf(Gender gender);
    Wolf(Gender gender, int age, int satiety);

    static int getFOV();

    string display() const override;

private:
    static const int _adultAge;
    static const int _lifespan;
    static const int _cooldown;
    static const int _maxSatiety;
    static const int _fov;
};

#endif // WOLF_H
