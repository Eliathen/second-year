/*! \file ship.cpp
    \brief Zawiera definicje metod klasy Ship
*/
#include "ship.hpp"

    Ship::Ship(int length){
        this->length = length;
        hitPoints = length;
        dir = 2;
}
