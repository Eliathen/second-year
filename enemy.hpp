/*! \file enemy.hpp
    \brief Zawiera deklaracje metod, oraz pola klasy Enemy
*/
#ifndef Enemy_H
#define Enemy_H
#include <iostream>
#include <cstdio>
#include <cstring>
#include <list>
#include <tuple>
#include <random>
#include <ctime>
#include <functional>
#include "to_string.hpp"
#include "ship.hpp"
#include "player.hpp"
#include "map.hpp"

//! Klasa Enemy
    /*!
        Zawiera odpowiednie pola oraz metody potrzebne do funkcjonowania przeciwnika
    */
class Enemy : public Player{
    public:
    bool prevHit;   /*!< zawiera informacje o tym czy poprzedni strzal byl trafieniem */
    int firstShootX,/*!< x pierwszego trafienia */
        shootX,     /*!< x strzalu */
        firstShootY,/*!< y pierwszego trafienia */
        shootY;     /*!< Y strzalu */
    bool left,      /*!< Zawiera informacje o tym czy przeciwnik ma strzelac dalej w lewo */
        right,      /*!< Zawiera informacje o tym czy przeciwnik ma strzelac dalej w prawo */
        up,         /*!< Zawiera informacje o tym czy przeciwnik ma strzelac dalej w gore */
        down;       /*!< Zawiera informacje o tym czy przeciwnik ma strzelac dalej w dol */
    bool checkedUp, /*!< Zawiera informacje o tym czy przeciwnik ma sprawdzic pole na gorze od ostatniego strzalu po trafieniu */
        checkedDown,/*!< Zawiera informacje o tym czy przeciwnik ma sprawdzic pole na dole od ostatniego strzalu po trafieniu */
        checkedLeft,/*!< Zawiera informacje o tym czy przeciwnik ma sprawdzic pole na lewo od ostatniego strzalu po trafieniu */
        checkedRight;/*!< Zawiera informacje o tym czy przeciwnik ma sprawdzic pole na prawo od ostatniego strzalu po trafieniu */
    std::list <Ship *>listOfShips; /*!< lista wskaznikow na statek przeciwnika */


    int enemyAttack(Map *playerMap);

    Enemy(std::string name);
    ~Enemy();
    void createShips(int two, int three, int four);
    void placeShips(Map *enemyMap);
    void resetLifePoints();
    int attackWithOutPrevHit(Map *playerMap);
    int shootUp(Map *playerMap);
    int shootDown(Map *playerMap);
    int shootLeft(Map *playerMap);
    int shootRight(Map *playerMap);
};
#endif
