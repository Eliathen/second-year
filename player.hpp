/*! \file player.hpp
    \brief Zawiera deklaracje metod, oraz pola klasy Player
*/
#ifndef Player_H
#define Player_H
#include <iostream>
#include <cstdio>
#include <cstring>
#include <list>
#include <tuple>
#include <functional>
#include <random>
#include <SFML/Graphics.hpp>

#include "ship.hpp"
#include "map.hpp"
/** Enum zawierajacy czynnosci gracza
*/
enum {
    SPREAD, /**<Rozstawianie */
    FIRE    /**<Strzelanie */
    };
/** Enum zawierajacy kierunki
*/
enum dir{
    dUp,    /**<Gora */
    dRight, /**<Prawo */
    dDown,  /**<Dol */
    dLeft}; /**<Lewo */
//! Klasa Player
/*!
    Zawiera odpowiednie pola oraz metody potrzebne do funkcjonowania gracza
*/
class Player{
    public:
    std::string name;                   /*!<Nazwa gracza */
    int lifePoints;                     /*!<Pola zajete przez gracza  */
    int mode;                           /*!<Tryb w jakim znajduje sie gracz  */
    int direction;                      /*!<Kierunek statku  */
    bool isSelected;                    /*!<Zawiera informacje czy gracz wybral statek  */
    bool isPossible;                    /*!<Zawiera informacje o tym czy w miejscu kursora mozna umiescic statek  */
    Ship *currentShip;                  /*!<Wskaznik na aktualnie rozmieszczany statek  */
    std::list <Ship *>listOfShips;      /*!<Lista wskaznikow na statek gracza  */

    bool playerAttack(Map *enemyMap, int x, int y);
    Player();
    void setName(std::string name);
    virtual ~Player();
    void createShips(int two, int three, int four);
    bool placeShipsInRandomPlace(Map *enemyMap);
    std::tuple<int, int> getCoordinate(int x, int y);
    virtual void resetLifePoints();
    void printAllShips(sf::RenderWindow &window);
    void changeShipStatus(int x, int y);
    void printChosenShip(sf::RenderWindow &window, int horizontal, int vertical);
    void changeDirection();
    bool isPossibleToPlace(Map *map, int x, int y);
    void cancelAddingShip();
    bool allSet();
    void resetAllShips();
};
#endif
