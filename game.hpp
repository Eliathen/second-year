/*! \file game.hpp
    \brief Zawiera deklaracje metod, oraz pola klasy Game
*/
#ifndef game_H
#define game_H

#include <cstring>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <unistd.h>
#include "to_string.hpp"
#include "map.hpp"
#include "ship.hpp"
#include "player.hpp"
#include "enemy.hpp"
/** Enum zawierajacy opcje
*/

enum menu{
    menu,           /**< opcja 1 */
    staticSpread,   /**< opcja 2 */
    autoSpread,     /**< opcja 3 */
    instruction,    /**< opcja 4 */
    quit            /**< opcja 5 */
    };
//! Klasa Game
    /*!
        Zawiera odpowiednie pola oraz metody potrzebne do funkcjonowania gry
    */
class Game{
    sf::RenderWindow window;                    /*!< obiekt glownego okna gry */
    Map *playerMap;                             /*!< wskaznik na mape gracza */
    Map *enemyMap;                              /*!< wskaznik na mape przeciwnika*/
    Player *Gamer;                              /*!< wskaznik na obiekt gracza*/
    Enemy *AI;                                  /*!< wskaznik na obiekt przeciwnika*/
    private:
    std::string optionInMenu[4];                /*!< tablica opcji*/
    sf::Text text;                              /*!< zmienna przechowujaca tekst w formacie biblioteki graficznej SFML*/
    sf::Font font;                              /*!< zmienna przechowujaca czcionke */
    sf::Text textResult;                        /*!< zmienna przechowujaca tekst o wyniku gry*/
    int menuStatus;                             /*!< zmienna przechowujaca status gry*/
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
