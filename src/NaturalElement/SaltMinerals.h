#ifndef SALTMINERALS_H
#define SALTMINERALS_H

#include "NaturalElement.h"


class SaltMinerals : public NaturalElement {
public:
    SaltMinerals();

    string display() const override;
    void incrementAge();
    bool shouldTransform() const;

private:
    int _age;
    static const int _lifespan;
};

#endif // SALTMINERALS_H
