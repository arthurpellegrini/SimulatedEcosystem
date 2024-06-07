#include "Gender.h"
#include <random>

Gender randomGender() {
    return rand() % 2 == 0 ? Gender::Male : Gender::Female;
}

ostream& operator<<(ostream &os, const Gender &gender) {
    if (gender == Gender::Female) return os << "F";
    if (gender == Gender::Male) return os << "M";
    return os << "Unknown";
}
