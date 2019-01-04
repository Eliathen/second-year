/*! \file player.hpp
    \brief Zawiera deklaracje metod, oraz pola klasy Player
*/
#ifndef ship_H
#define ship_H
#include <iostream>
#include <cstdio>
#include <cstring>
/** Enum zawierajacy stan statku
*/
enum placed{
    PLACED,     /**<Rozstawiony */
    DURING,     /**<W trakcie rozstawiania */
    NOTPLACED   /**<Nie rozstawiony */
    };
//! Klasa Ship
/*!
    Zawiera odpowiednie pola potrzebne do funkcjonowania statku
*/
class Ship{
    public:
    int length;
    int hitPoints;
    int dir;
    int X;
    int Y;
    int isPlaced;
    Ship(int length);
};

#endif
