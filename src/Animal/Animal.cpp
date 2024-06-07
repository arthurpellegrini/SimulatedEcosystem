#include "Animal.h"

Animal::Animal(const Gender gender, const int adultAge, const int lifespan, const int maxSatiety, const int cooldown)
    : Animal(gender, 0, adultAge, lifespan,  maxSatiety, maxSatiety, cooldown) {}

Animal::Animal(const Gender gender, const int age, const int adultAge, const int lifespan, const int satiety, const int maxSatiety, const int cooldown)
    : _gender(gender), _age(age), _adultAge(adultAge), _lifespan(lifespan), _satiety(satiety), _maxSatiety(maxSatiety), _cooldown(cooldown), _breedCooldown(0) {
}

Animal::~Animal() = default;

void Animal::move()
{
    _canMove = false;
}
bool Animal::canMove() const
{
    return _canMove;
}
void Animal::resetCanMove()
{
    _canMove = true;
}


void Animal::increaseAge()
{
    _age++;
    updateBreedCooldown();
}
bool Animal::isOldAgeDead() const
{
    return _age >= _lifespan;
}
bool Animal::isHungerDead() const
{
    return _satiety <= 0;
}

void Animal::eat()
{
    _satiety = _maxSatiety;
}
void Animal::decreaseSatiety()
{
    _satiety--;
}

void Animal::breed()
{
    _canBreed = false;
    _breedCooldown = _cooldown;
}

void Animal::updateBreedCooldown()
{
    if (_breedCooldown > 0)
    {
        _breedCooldown--;
        if (_breedCooldown == 0)
        {
            _canBreed = true;
        }
    }
}
bool Animal::canBreed() const
{
    return _canBreed && _age > _adultAge;
}
bool Animal::canBreedWith(const Animal &animal) const {
    return canBreed() && animal.canBreed() && (_gender == Gender::Female && animal.getGender() == Gender::Male);
}

Gender Animal::getGender() const { return _gender; }
int Animal::getAge() const { return _age; }
int Animal::getAdultAge() const { return _adultAge; }
int Animal::getSatiety() const { return _satiety; }


ostream& operator<<(ostream &os, const Animal &animal) {
    return os << animal.display();
}