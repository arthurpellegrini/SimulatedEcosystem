#ifndef SALTMINERALS_H
#define SALTMINERALS_H

#include "NaturalElement.h"

class SaltMinerals : public NaturalElement {
    static const int _lifespan = 1;
    int _age;

public:
    SaltMinerals();

    string display() const override;
    void incrementAge();
    bool shouldTransform() const;
};

#endif // SALTMINERALS_H
