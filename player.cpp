#include "player.hpp"

    Player::Player(){
        lifePoints = 0;
        mode = SPREAD;
        currentShip = NULL;
    }

    void Player::setName(std::string name){
        this->name = name;
    }
    Player::~Player(){
        for(std::list<Ship*>::iterator it = listOfShips.begin(); it!=listOfShips.end(); it++){
            delete *it;
        }
    }
    void Player::createShips(int two, int three, int four){
        int x = 410;
        int y = 180;
        for(int j=0; j<two; j++){
            Ship* player_ship=new Ship(2);
            if(!player_ship){
                //wyjatek
            }
            listOfShips.push_back(player_ship);
            lifePoints=lifePoints+player_ship->hitPoints;
            player_ship->isPlaced = NOTPLACED;
            player_ship->X = x;
            player_ship->Y = y;
            y=y+2*40+15;
        }
        y = 180;
        x += 50;
        for(int j=0; j<three; j++){
            Ship* player_ship=new Ship(3);
            if(!player_ship){
                //wyjatek
            }
            listOfShips.push_back(player_ship); 
            lifePoints=lifePoints+player_ship->hitPoints;
            player_ship->isPlaced = NOTPLACED;
            player_ship->X = x;
            player_ship->Y = y;
            y = y+3*40 + 15;

        }
        y = 180;
        x += 50;
        for(int j=0; j<four; j++){
            Ship* player_ship=new Ship(4);
            if(!player_ship){
                //wyjatek
            }
            listOfShips.push_back(player_ship);
            lifePoints=lifePoints+player_ship->hitPoints;
            player_ship->isPlaced = NOTPLACED;
            player_ship->X = x;
            player_ship->Y = y;
            y = y+4*40 + 15;
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

    bool Player::playerAttack(Map *enemyMap, int row, int col){
            if(enemyMap->fieldsStatus[row][col]==1){//Trafiono w statek
                enemyMap->fieldsStatus[row][col]=2;
                enemyMap->grid[row][col]->hitPoints--;
                enemyMap->grid[row][col]=NULL;
                return true;
            }
            else if(enemyMap->fieldsStatus[row][col]==0){//trafiono w puste pole
                enemyMap->fieldsStatus[row][col]=3;
                return false;
            }
        return false;
    }
    bool Player::placeShipsInRandomPlace(Map *playerMap){
        auto random = std::bind(std::uniform_int_distribution<>(1,10),
        std::mt19937(time(NULL)));
        std::list<Ship*>::iterator it = listOfShips.begin();
        while(it!=listOfShips.end()){
            bool done=false;
            while(!done){
                int numberOfTry = 0;
                int row=0;
                int col=0;
                row=random();
                col=random();
                    if(numberOfTry==4){
                        row=random();
                        col=random();
                    }
                    (*it)->dir = std::rand()%4;
                    done=playerMap->setShipUsingXandY(*it, row, col);
                    if(done==true){
                        it++;
                    }
                    numberOfTry++;
            }
        }
        return true;
    }
    void Player::printAllShips(sf::RenderWindow &window){
        sf::Texture destroyedPlayer, ship, destroyedEnemy;
        if(!destroyedPlayer.loadFromFile("pictures/destroyedPartShip.png") ||
            !destroyedEnemy.loadFromFile("pictures/destroyedEnemyPartShip.png")||
            !ship.loadFromFile("pictures/ShipField.png")){
            //nie udalo sie wczytac tekstury;  
        }
        sf::Sprite sprite;
        sprite.setScale(0.90,0.90);
        for(std::list<Ship*>::iterator it=listOfShips.begin(); it!=listOfShips.end(); it++){
            int x = (*it)->X;
            int y = (*it)->Y;
            if((*it)->isPlaced==NOTPLACED){    
                for(int i =0; i<(*it)->length; i++){
                    sprite.setTexture(ship);
                    sprite.setPosition(x,y);
                    y+=40;
                    window.draw(sprite);
                }
            }
        }   
    }
    void Player::printChosenShip(sf::RenderWindow &window, int horizontal, int vertical){ 
        sf::Texture destroyedPlayer, ship, destroyedEnemy;
        if(!destroyedPlayer.loadFromFile("pictures/destroyedPartShip.png") ||
            !destroyedEnemy.loadFromFile("pictures/destroyedEnemyPartShip.png")||
            !ship.loadFromFile("pictures/ShipField.png")){
            //nie udalo sie wczytac tekstury  
            //wyjatek
        }
        vertical-=20;
        horizontal-=20;
        sf::Sprite sprite;
        sprite.setScale(0.85,0.85);
        if(isPossible){
            sprite.setTexture(destroyedEnemy);

        }
        else{
            sprite.setTexture(destroyedPlayer);
        }
        for(std::list<Ship*>::iterator it=listOfShips.begin(); it!=listOfShips.end(); it++){
            if((*it)->isPlaced==DURING){
                    if((*it)->dir==0){
                        for(int i =0; i<(*it)->length; i++){
                            sprite.setPosition(horizontal,vertical);
                            vertical-=35;
                            window.draw(sprite);
                        }
                    }
                    if((*it)->dir==1){
                        for(int i =0; i<(*it)->length; i++){
                            sprite.setPosition(horizontal,vertical);
                            horizontal+=35;
                            window.draw(sprite);;
                        }
                    }
                    if((*it)->dir==2){
                        for(int i =0; i<(*it)->length; i++){
                            sprite.setPosition(horizontal,vertical);
                            vertical+=35;
                            window.draw(sprite);
                        }
                    }
                    if((*it)->dir==3){
                        for(int i =0; i<(*it)->length; i++){
                            sprite.setPosition(horizontal,vertical);
                            horizontal-=35;
                            window.draw(sprite);
                        }

                    }
            }
        } 
    }
    void Player::changeShipStatus(int x, int y){
        for(std::list<Ship*>::iterator it=listOfShips.begin(); it!=listOfShips.end(); it++){
            if(x>(*it)->X && x<((*it)->X+40) && y>(*it)->Y && y<((*it)->Y+40) && !isSelected && (*it)->isPlaced==NOTPLACED){
                (*it)->isPlaced = DURING;
                isSelected = true;
                currentShip = *it;
            }
        }
    }
    void Player::changeDirection(){
        if(currentShip->isPlaced==DURING){
            currentShip->dir = (currentShip->dir+1)%4;
        }     
    }
    bool Player::isPossibleToPlace(Map *map, int x, int y){
        if(x>34 && x<380 && y>167 && y<528 && currentShip!=NULL){
            auto cell = getCoordinate(x,y);
            if(currentShip->dir==dUp){
                if((y-((currentShip->length)-1)*40)>167 && map->checkUp(std::get<0>(cell), std::get<1>(cell), currentShip->length)){
                    return true;
                }
                else{
                    return false;
                }
            }
            if(currentShip->dir==dRight){
                if((x+((currentShip->length)-1)*40)<400 && map->checkRight(std::get<0>(cell), std::get<1>(cell), currentShip->length)){
                    return true;
                }
                else{
                    return false;
                }
            }
            if(currentShip->dir==dDown){
                if((y+((currentShip->length)-1)*40)<538 && map->checkDown(std::get<0>(cell), std::get<1>(cell), currentShip->length)){
                    return true;
                }
                else{
                    return false;
                }
            }
            if(currentShip->dir==dLeft){
               if((x-((currentShip->length)-1)*40)>34 && map->checkLeft(std::get<0>(cell), std::get<1>(cell), currentShip->length)){
                    return true;
                }
                else{
                    return false;
                }
            }
        }
        else{
            return false;
        }
        return false;

    }
    void Player::cancelAddingShip(){
        currentShip->isPlaced=NOTPLACED;
        currentShip->dir = dDown;
        isPossible = false;
        isSelected = false;
        currentShip = NULL;
    }
    bool Player::allSet(){
        for(std::list<Ship*>::iterator it = listOfShips.begin(); it!=listOfShips.end(); it++){
            if((*it)->isPlaced==PLACED){
            }
            else{
                return false;
            }
        }
        return true;
    }
    void Player::resetAllShips(){
        for(std::list<Ship*>::iterator it = listOfShips.begin(); it!=listOfShips.end(); ++it){
            (*it)->dir = dDown;
            (*it)->isPlaced = NOTPLACED;
        }
    }