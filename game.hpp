#ifndef game_H
#define game_H

#include <cstring>
#include <fstream> 
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "map.hpp"
#include "ship.hpp"
#include "player.hpp"
#include "enemy.hpp"
enum menu{menu, staticSpread, autoSpread, instruction, quit};

class Game{
    sf::RenderWindow window;
    Map *playerMap;
    Map *enemyMap;
    Player *Gamer;
    Enemy *AI;
    private:
    std::string optionInMenu[4];
    sf::Text text;
    sf::Font font;
    sf::Text textResult;
    int menuStatus;
    public:
    Game();
    ~Game();
    void startGame();
    void printStatment(std::string statment);
    void setResult(int result);
    void showGame(sf::Sprite gameBackground);
    void showGame(sf::Sprite gameBackground, sf::Sprite reset);
    void setMenuOptions();
    void showMenu(sf::Sprite menuBackground);
    void showInstruction(sf::Sprite clearBackground);
    void newGame();
    void downloadInstruction(std::string *inst);
    void showGameDuringStaticSpread(sf::Sprite gameBackground, int x, int y);
};

#endif
