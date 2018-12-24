#include "player.hpp"

    Player::Player(){
        lifePoints = 0;
        mode = SPREAD;
    }

    void Player::setName(std::string name){
        this->name = name;
    }
    Player::~Player(){
            //usuwanie listy statkow
            for(std::list<Ship*>::iterator it = listOfShips.begin(); it!=listOfShips.end(); it++){
                delete *it;
            }
    }
    void Player::createShips(int two, int three, int four){
        for(int j=0; j<two; j++){
            Ship* player_ship=new Ship(2);
            listOfShips.push_back(player_ship);
            lifePoints=lifePoints+player_ship->hitPoints;
        }
        for(int j=0; j<three; j++){
            Ship* player_ship=new Ship(3);
            listOfShips.push_back(player_ship); 
            lifePoints=lifePoints+player_ship->hitPoints;
        }
        for(int j=0; j<four; j++){
            Ship* player_ship=new Ship(4);
            listOfShips.push_back(player_ship);
            lifePoints=lifePoints+player_ship->hitPoints;
        }
    }
    void Player::resetLifePoints(){
        lifePoints = 0;
        for(std::list<Ship*>::iterator it = listOfShips.begin(); it!=listOfShips.end(); it++){
                this->lifePoints = this->lifePoints + (*it)->length;
        }
    }
    std::tuple<int, int> Player::getCoordinate(int x, int y){
        int indexX =0, indexY = 0;
        if(mode==SPREAD){
            indexY = (x - 35)/36;
            indexX = (y - 168)/37;
            indexX++;
            indexY++;
            if(indexX<11 && indexX>0 && indexY<11 && indexY>0){
                return std::make_pair(indexX, indexY);
            }
            else{
                indexX=0, indexY = 0;
            }
        }
        if(mode==FIRE){
            indexY = (x-560)/36;
            indexX = (y-168)/37;
            indexX++;
            indexY++;
            if(indexX<11 && indexX>0 && indexY<11 && indexY>0){
                return std::make_pair(indexX, indexY);
            }
            else{
                indexX=0, indexY = 0;
            }
        }
        return std::make_pair(indexX, indexY);
    }

    bool Player::playerAttack(Map *enemyMap, int x, int y){
            if(enemyMap->fieldsStatus[x][y]==1){//Trafiono w statek
                enemyMap->fieldsStatus[x][y]=2;
                enemyMap->grid[x][y]->hitPoints--;
                enemyMap->grid[x][y]=NULL;
                return true;
            }
            else if(enemyMap->fieldsStatus[x][y]==0){//trafiono w puste pole
                enemyMap->fieldsStatus[x][y]=3;
                return false;
            }
        else return false;
    }
    bool Player::placeShipsInRandomPlace(Map *playerMap){
        bool firstFieldStatus;
        auto random = std::bind(std::uniform_int_distribution<>(1,10),
        std::mt19937(time(NULL)));
        std::list<Ship*>::iterator it = listOfShips.begin();
        while(it!=listOfShips.end())
        {
                int numberOfTry = 0;
                int row, col=0;
                row=random();
                col=random();;
                firstFieldStatus = playerMap->setFirstPartOfShip(*it,row, col);
                bool done=false;
                while(!done && firstFieldStatus == true){
                    if(numberOfTry==4){
                        playerMap->clearPlace(row,col);
                        break;
                    }
                    direction=std::rand()%4;
                    done=playerMap->setShipUsingXandY(*it, row, col, direction);
                    if(done==true){
                        it++;
                    }
                    numberOfTry++;
                }
        }
        return true;
    }