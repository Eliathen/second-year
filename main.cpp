#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

#include "game.hpp"

int main(){

    Game *game = new Game();
    if(!game){
        //wyjatek
    }
    game->Game::startGame();
    delete game;
    
    return 0;
}
