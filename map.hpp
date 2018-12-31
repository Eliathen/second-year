#ifndef map_H
#define map_H
#include <iostream>
#include <cstdio>
#include <cstring>
#include <SFML/Graphics.hpp>

#include "ship.hpp"

enum {UP, RIGHT, DOWN, LEFT};

class Map{
    public:
    Ship *grid[12][12];
    int fieldsStatus[12][12];
    std::string name;

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