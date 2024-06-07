#ifndef NATURALELEMENT_H
#define NATURALELEMENT_H

#include <string>

using namespace std;


class NaturalElement {
public:
    virtual ~NaturalElement() = default;
    virtual string display() const;
};

ostream& operator<<(ostream &os, const NaturalElement &naturalElement);

#endif // NATURALELEMENT_H
