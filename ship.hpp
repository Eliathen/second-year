#ifndef ship_H
#define ship_H
#include <iostream>
#include <cstdio>
#include <cstring>
enum placed{PLACED, DURING, NOTPLACED};

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