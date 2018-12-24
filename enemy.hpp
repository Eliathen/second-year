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

#include "ship.hpp"
#include "player.hpp"
#include "map.hpp"

class Enemy : public Player{
    public:
    bool prevHit;
    int firstShootX, shootX, firstShootY, shootY;
    bool left, right, up, down;
    bool checkedUp, checkedDown, checkedLeft, checkedRight;
    std::list <Ship *>listOfShips;


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