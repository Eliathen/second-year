/*! \file map.hpp
    \brief Zawiera deklaracje metod, oraz pola klasy Map
*/
#ifndef map_H
#define map_H
#include <iostream>
#include <cstdio>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "to_string.hpp"
#include "ship.hpp"
/** Enum zawierajacy kierunki na mapie
*/
enum {
    UP,     /**<gora */
    RIGHT,  /**<prawo */
    DOWN,   /**<dol */
    LEFT    /**<lewo*/
    };
//! Klasa Map
/*!
    Zawiera odpowiednie pola oraz metody potrzebne do funkcjonowania map gracza oraz przeciwnika
*/
class Map{
    public:
    Ship *grid[12][12];         /*!< tablica wskaznikow na statek */
    int fieldsStatus[12][12];   /*!< tablica stanu pol */
    std::string name;           /*!< nazwa wlasciciela mapy */

   public:
    Map(std::string nazwa);
    ~Map();
    void printMap(sf::RenderWindow &window);
    bool checkUp(int x, int y, int len);
    bool checkDown(int x, int y, int len);
    bool checkLeft(int x, int y, int len);
    bool checkRight(int x, int y, int len);
    bool setShipUsingXandY(Ship *ship, int x, int y);
    void clearPlace(int x,int y);
    void clearMap();
};
#endif
