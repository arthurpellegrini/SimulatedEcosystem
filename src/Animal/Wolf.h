#ifndef WOLF_H
#define WOLF_H

#include "Animal.h"


class Wolf : public Animal {
public:
    Wolf(Gender gender);
    Wolf(int age, int satiety, Gender gender);

    string display() const override;
    void eat() override;
    void move() override;
    void breed() override;
    void die() override;

    static int getLifespan();

private:
    static const int _maxSatiety;
    static const int _lifespan;
    static const int _fov; // Field of view for movement
};

#endif // WOLF_H
