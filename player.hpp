#ifndef Player_H
#define Player_H
#include <iostream>
#include <cstdio>
#include <cstring>
#include <list>
#include <tuple> 
#include <functional>
#include <random>

#include "ship.hpp"
#include "map.hpp"

enum {SPREAD, FIRE};

class Player{
    public:
    std::string name;
    int lifePoints;
    int mode;
    int direction;
    std::list <Ship *>listOfShips;

    bool playerAttack(Map *enemyMap, int x, int y);
    Player();
    void setName(std::string name);
    virtual ~Player();
    void createShips(int two, int three, int four);
    bool placeShipsInRandomPlace(Map *enemyMap);
    std::tuple<int, int> getCoordinate(int x, int y);
    virtual void resetLifePoints();
};
#endif