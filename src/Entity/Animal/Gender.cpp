#include "Gender.h"
#include <random>

Gender randomGender() {
    return rand() % 2 == 0 ? Gender::Male : Gender::Female;
}