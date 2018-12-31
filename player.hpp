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

enum {SPREAD, FIRE};
enum dir{dUp, dRight, dDown, dLeft};

class Player{
    public:
    std::string name;
    int lifePoints;
    int mode;
    int direction;
    bool isSelected;
    bool isPossible;
    Ship *currentShip;
    std::list <Ship *>listOfShips;

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