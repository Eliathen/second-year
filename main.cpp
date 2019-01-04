/*! \file main.cpp
    \brief Glowny plik projektu.
*/
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

#include "game.hpp"
//! Funkcja main
/*!
    \brief
    \return Zwraca 0 po zakonczeniu programu.
*/
int main(){
    Game *game = new Game();
    try{
        if(!game) throw "Error during creation of game! Application will close in";
    } catch(const char *err){
        sf::RenderWindow exception_window;
        exception_window.create(sf::VideoMode(550, 200, 60), "Critical error!", sf::Style::Close);
        sf::Text error_text;
        sf::Text counting;
        sf::Font font;
        font.loadFromFile("pictures/arial.ttf");
        int c=5;
        counting.setString(to_string(c));
        counting.setFont(font);
        counting.setCharacterSize(20);
        counting.setPosition(20,80);
        error_text.setString(err);
        error_text.setFont(font);
        error_text.setCharacterSize(20);
        error_text.setPosition(20,60);
        while(exception_window.isOpen()){
            counting.setString(to_string(c));
            exception_window.draw(error_text);
            exception_window.draw(counting);
            exception_window.display();
            sf::sleep(sf::milliseconds(1000));
            c--;
            counting.setString(to_string(c));
            if(c==0){
                exception_window.close();
            }
            exception_window.clear();
        }
        exit(0);
    }
    game->Game::startGame();
    delete game;

    return 0;
}
