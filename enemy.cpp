#include "enemy.hpp"

    Enemy::Enemy(std::string name){
        this->name = name;
        lifePoints = 0;
        prevHit = false;
    }
    Enemy::~Enemy(){
            for(std::list<Ship*>::iterator it = listOfShips.begin(); it!=listOfShips.end(); it++){
                delete *it;
            }
    }
    void Enemy::createShips(int two, int three, int four){
        for(int j=0; j<two; j++){
            Ship* player_ship=new Ship(2);
            if(!player_ship){
                //wyjatek
            }
            listOfShips.push_back(player_ship);
            lifePoints=lifePoints+player_ship->hitPoints;
            player_ship->isPlaced = 0;
            player_ship->X = 0;
            player_ship->Y = 0;
        }
        for(int j=0; j<three; j++){
            Ship* player_ship=new Ship(3);
            if(!player_ship){
                //wyjatek
            }
            listOfShips.push_back(player_ship); 
            lifePoints=lifePoints+player_ship->hitPoints;
            player_ship->isPlaced = 0;
            player_ship->X = 0;
            player_ship->Y = 0;
        }
        for(int j=0; j<four; j++){
            Ship* player_ship=new Ship(4);
            if(!player_ship){
                //wyjatek
            }
            listOfShips.push_back(player_ship);
            lifePoints=lifePoints+player_ship->hitPoints;
            player_ship->isPlaced = 0;
            player_ship->X = 0;
            player_ship->Y = 0;
        }
    }
    void Enemy::resetLifePoints(){
        lifePoints = 0;
        for(std::list<Ship*>::iterator it = listOfShips.begin(); it!=listOfShips.end(); it++){
                this->lifePoints = this->lifePoints + (*it)->length;
        }
    }
    void Enemy::placeShips(Map *enemyMap){
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
                    done=enemyMap->setShipUsingXandY(*it, row, col);
                    if(done==true){
                        it++;
                    }
                    numberOfTry++;
            }
        }
    }
    int Enemy::enemyAttack(Map *playerMap){
        if(!prevHit){
            return (attackWithOutPrevHit(playerMap));
        }
        else{
            int isShoot;
            if((shootX-1)>0 && checkedUp==false){
                isShoot = shootUp(playerMap);
                checkedUp = true;
                return isShoot;
            }
            if(up==true){
                isShoot = shootUp(playerMap);
                checkedLeft=checkedRight = true;
                return isShoot;
            }
            if((shootY+1)<11 && checkedRight==false){
                isShoot = shootRight(playerMap);
                checkedRight = true;
                return isShoot;
            }
            if(right==true){
                isShoot = shootRight(playerMap);
                checkedDown=checkedUp = true;
                return isShoot;
            }
            if((shootX+1)<11 && checkedDown==false){
                isShoot = shootDown(playerMap);
                checkedDown = true;
                return isShoot;
            }
            if(down==true){
                isShoot = shootDown(playerMap);
                checkedLeft=checkedRight = true; 
                return isShoot;
            }
            if((shootY-1)>0 && checkedLeft==false){
                isShoot = shootLeft(playerMap);
                checkedLeft = true;
                return isShoot;
            }
            if(left==true){
                isShoot = shootLeft(playerMap);
                checkedDown=checkedUp = true; 
                return isShoot;
            }
            prevHit=false;
            checkedDown=checkedLeft=checkedRight=checkedUp=false;
            up=down=left=right=false;
            isShoot = attackWithOutPrevHit(playerMap);
            return isShoot;

        }
    }
    int Enemy::shootUp(Map *playerMap){
        if((shootX-1)>0 && playerMap->fieldsStatus[shootX-1][shootY]==1){
            playerMap->fieldsStatus[shootX-1][shootY]=2;
            shootX=shootX - 1;
            up = true;
            left=right=false;
            return 1;
        }
        else if((shootX-1)>0 && playerMap->fieldsStatus[shootX-1][shootY]==0){
            playerMap->fieldsStatus[shootX-1][shootY]=3;
            shootX = firstShootX;
            shootY = firstShootY;
            up = false;
            return 0;
        }
        shootX=firstShootX;
        shootY=firstShootY;
        up = false;
        return 2;
    }
    int Enemy::shootDown(Map *playerMap){
        if((shootX+1)<11 && playerMap->fieldsStatus[shootX+1][shootY]==1){
            playerMap->fieldsStatus[shootX+1][shootY]=2;
            shootX = shootX + 1;
            down = true;
            left=right=false;
            return 1;
        }
        else if((shootX+1)<11 && playerMap->fieldsStatus[shootX+1][shootY]==0){
            playerMap->fieldsStatus[shootX+1][shootY]=3;
            shootX = firstShootX;
            shootY = firstShootY;
            down = false;
            return 0;
        }
        shootX=firstShootX;
        shootY=firstShootY;
        down = false;
        return 2;
    }
    int Enemy::shootLeft(Map *playerMap){
        if((shootY-1)>0 && playerMap->fieldsStatus[shootX][shootY-1]==1){
            playerMap->fieldsStatus[shootX][shootY-1]=2;
            shootY = shootY - 1;
            left = true;
            up=down=false;
            return 1;
        }
        else if((shootY-1)>0 && playerMap->fieldsStatus[shootX][shootY-1]==0){
            playerMap->fieldsStatus[shootX][shootY-1]=3;
            shootX = firstShootX;
            shootY = firstShootY;
            left = false;
            return 0;
        }
        shootX=firstShootX;
        shootY=firstShootY;
        left = false;
        return 2;
    }
    int Enemy::shootRight(Map *playerMap){
        if((shootY+1)<11 && playerMap->fieldsStatus[shootX][shootY+1]==1){
            playerMap->fieldsStatus[shootX][shootY+1]=2;
            shootY = shootY + 1;
            right = true;
            up=down=false;
            return 1;
        }
        else if((shootY+1)<11 && playerMap->fieldsStatus[shootX][shootY+1]==0){
            playerMap->fieldsStatus[shootX][shootY+1]=3;
            shootX = firstShootX;
            shootY = firstShootY;
            right = false;
            return 0;
        }
        shootX=firstShootX;
        shootY=firstShootY;
        right = false;
        return 2;
    }
    int Enemy::attackWithOutPrevHit(Map *playerMap){
        checkedDown=checkedLeft=checkedRight=checkedUp= false;
            int indexX, indexY;
            auto random = std::bind(std::uniform_int_distribution<>(1,10),
            std::mt19937(time(NULL)));
            do{
                indexX = random();
                indexY = random();
            }while(playerMap->fieldsStatus[indexX][indexY]!=0 && playerMap->fieldsStatus[indexX][indexY]!=1);

            if(playerMap->fieldsStatus[indexX][indexY]==1){
                playerMap->fieldsStatus[indexX][indexY]=2;
                (playerMap->grid[indexX][indexY]->hitPoints)--;
                playerMap->grid[indexX][indexY]=NULL;
                firstShootX = shootX = indexX;
                firstShootY = shootY = indexY;
                prevHit = true;
                return 1;
            }
            if(playerMap->fieldsStatus[indexX][indexY]==0){
                playerMap->fieldsStatus[indexX][indexY]=3;
                return 0;
            } 
            return 0;       
    }
    