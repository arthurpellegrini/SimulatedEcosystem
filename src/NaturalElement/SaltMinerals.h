/**
 * Project Untitled
 */


#ifndef _SALTMINERALS_H
#define _SALTMINERALS_H

#include "NaturalElement.h"


class SaltMinerals: public NaturalElement {

public:
    SaltMinerals();

    std::string display() const override {
        return ",";
    }

private: 
    static int lifespan;
    int age;
};

int SaltMinerals::lifespan = 1;


#endif //_SALTMINERALS_H