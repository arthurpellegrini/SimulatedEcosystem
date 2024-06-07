#ifndef WOLF_H
#define WOLF_H

#include "Animal.h"


class Wolf : public Animal {
public:
    explicit Wolf(Gender gender);
    Wolf(Gender gender, int age, int satiety);

    string display() const override;

private:
    static const int _maxSatiety;
    static const int _lifespan;
};

#endif // WOLF_H
