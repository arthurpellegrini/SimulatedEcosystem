#include "Animal.h"

const int Animal::_breedCooldown = 5;
const int Animal::_adultAge = 10;

Animal::Animal(Gender gender, int maxSatiety, int lifespan)
    : _age(0), _gender(gender), _satiety(maxSatiety), _maxSatiety(maxSatiety), _lifespan(lifespan) {}
Animal::Animal(Gender gender, int maxSatiety, int lifespan, int age, int satiety)
    : _age(age), _gender(gender), _satiety(satiety), _maxSatiety(maxSatiety), _lifespan(lifespan) {}

Animal::~Animal() = default;

void Animal::move() {
    _canMove = false;
}

bool Animal::canMove() const { return _canMove; }
void Animal::resetCanMove() { _canMove = true; }


void Animal::increaseAge() { _age++; if(_age == _adultAge) _lastBreed=_breedCooldown; if (_lastBreed != -1) _lastBreed++;}
bool Animal::isOldAgeDead() const { return _age >= _lifespan; }
bool Animal::isHungerDead() const { return _satiety <= 0; }

void Animal::eat() { _satiety = _maxSatiety; }
void Animal::decreaseSatiety() { _satiety--; }

bool Animal::canBreed(const Animal &animal) const {
    if(this->_gender != animal.getGender()) {
        if(!_isBreeding && !animal.isBreeding())
            if(_lastBreed > _breedCooldown)
                return true;
    }
    return false;
}
void Animal::breed() { _lastBreed = 0; }

bool Animal::isBreeding() const { return _isBreeding; }
void Animal::setIsBreeding(bool isBreeding) { _isBreeding = isBreeding; }


int Animal::getAge() const { return _age; }
int Animal::getAdultAge() { return _adultAge; }
Gender Animal::getGender() const { return _gender; }
int Animal::getSatiety() const { return _satiety; }

ostream& operator<<(ostream &os, const Animal &animal) {
    if (animal.getAge()< Animal::getAdultAge()) return os << "a";
    return os << animal.display();
}