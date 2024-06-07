#include "NaturalElement.h"

string NaturalElement::display() const {
    return "&";
}

ostream& operator<<(ostream &os, const NaturalElement &naturalElement) {
    return os << naturalElement.display();
}