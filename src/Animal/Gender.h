#ifndef GENDER_H
#define GENDER_H
#include <ostream>

using namespace std;

enum class Gender {
    Male,
    Female
};

Gender randomGender();
ostream& operator<<(ostream &os, const Gender &gender);

#endif //GENDER_H
