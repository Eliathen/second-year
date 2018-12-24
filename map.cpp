#include "map.hpp"

    /*
        Map() : grid(0), fieldsStatus(0) {
            //memset(grid, 0, 100*sizeof(int));
            //memset(fieldsStatus, 0, 100*sizeof(int));
    }
    */
    Map::Map(std::string nazwa){
        memset(grid, 0, 144*sizeof(int));
        memset(fieldsStatus, 0, 144*sizeof(int));
        for(int i=0; i<12; i++){
            fieldsStatus[0][i]=-1;
            fieldsStatus[11][i]=-1;
            fieldsStatus[i][0]=-1;
            fieldsStatus[i][11]=-1;
        }
        name = nazwa;
    }
    Map::~Map(){
    }
    void Map::printMap(sf::RenderWindow &window){
        //fieldsStatus[5][5]=1;
        sf::Texture empty, destroyedPlayer, ship, miss, destroyedEnemy;
        if(!empty.loadFromFile("pictures/EmptyField.png") ||
            !destroyedPlayer.loadFromFile("pictures/destroyedPartShip.png") ||
            !destroyedEnemy.loadFromFile("pictures/destroyedEnemyPartShip.png")||
            !ship.loadFromFile("pictures/ShipField.png")||
            !miss.loadFromFile("pictures/missAttack.png")){
            //nie udalo sie wczytac tekstury;  
            }
        sf::Sprite sprite;
        sprite.setScale(0.84,0.84);
        int xPlayer = 35, xEnemy = 560, Y = 168;
        for(int i=1; i<11; i++){
            for(int j=1; j<11; j++){
                if(name=="AI"){
                    if(fieldsStatus[i][j]==0 || fieldsStatus[i][j]==1){
                    //Puste pole lub na polu znajduje się statek przeciwnika. Rysowanie pola w kolorze szarym
                        sprite.setTexture(empty);
                        sprite.setPosition(xEnemy,Y);
                    }
                    if(fieldsStatus[i][j]==2){
                        //Zatopiony fragment statku. Rysowanie pola w kolorze zielonym
                        sprite.setTexture(destroyedEnemy);
                        sprite.setPosition(xEnemy,Y);
                    }
                    if(fieldsStatus[i][j]==3){
                        //Trafione puste pole. Rysowanie pola w kolorze niebieskim
                        sprite.setTexture(miss);
                        sprite.setPosition(xEnemy,Y);
                    }
                    xEnemy = xEnemy+36;
                }
                else{
                    if(fieldsStatus[i][j]==0){
                        //Puste pole. Rysowanie pola w kolorze szarym
                        sprite.setTexture(empty);
                        sprite.setPosition(xPlayer,Y);
                        
                    }
                    else if(fieldsStatus[i][j]==1){
                        //Na polu znajduje się statek. Rysowanie pola w kolorze zoltymm
                        sprite.setTexture(ship);
                        sprite.setPosition(xPlayer,Y);
                    }
                    else if(fieldsStatus[i][j]==2){
                        //Zatopiony fragment statku. Rysowanie pola w kolorze czerwonym
                        sprite.setTexture(destroyedPlayer);
                        sprite.setPosition(xPlayer,Y);
                    }
                    else if(fieldsStatus[i][j]==3){
                        //polet trafione. Bylo puste
                        sprite.setTexture(miss);
                        sprite.setPosition(xPlayer,Y);
                    }
                    xPlayer= xPlayer+36;
                }
                window.draw(sprite);
            }
            xPlayer=35;
            xEnemy=560;
            Y= Y+37;
        }
    }
    bool Map::checkUp(int x, int y, int len){
        for(int i=1; i<len; ++i){       
            if(fieldsStatus[x-i][y]!=0 ||
                (fieldsStatus[x-i-1][y]!=0 && fieldsStatus[x-i-1][y]!=-1)||
                (fieldsStatus[x-i][y+1]!=0 && fieldsStatus[x-i][y+1]!=-1)||
                (fieldsStatus[x-i][y-1]!=0 && fieldsStatus[x-i][y-1]!=-1)){
                return false;
            }
        }
        return true;

    }
    bool Map::checkDown(int x, int y, int len){
        for(int i=1; i<len; ++i){        
            if(fieldsStatus[x+i][y]!=0 ||
                (fieldsStatus[x+i+1][y]!=0 && fieldsStatus[x+i+1][y]!=-1)||
                (fieldsStatus[x+i][y-1]!=0 && fieldsStatus[x+i][y-1]!=-1)||
                (fieldsStatus[x+i][y+1]!=0 && fieldsStatus[x+i][y+1]!=-1)){
                return false;
            }
        }
        return true;

    }
    bool Map::checkLeft(int x, int y, int len){
        for(int i=1; i<len; ++i){
            if(fieldsStatus[x][y-i]!=0 ||
                (fieldsStatus[x-1][y-i]!=0 && fieldsStatus[x-1][y-i]!=-1)||
                (fieldsStatus[x+1][y-i]!=0 && fieldsStatus[x+1][y-i]!=-1)||
                (fieldsStatus[x][y-i-1]!=0 && fieldsStatus[x][y-i-1]!=-1)
                ){

                return false;
            }
            
        }
        return true;
    }
    bool Map::checkRight(int x, int y, int len){
        for(int i=1; i<len; ++i){
            if(fieldsStatus[x][y+i] ||
                (fieldsStatus[x-1][y+i]!=0 && fieldsStatus[x-1][y+i]!=-1)||
                (fieldsStatus[x+1][y+i]!=0 && fieldsStatus[x+1][y+i]!=-1)||
                (fieldsStatus[x][y+i+1]!=0 && fieldsStatus[x][y+i+1]!=-1)
                ){

                return false;
            }
            
        }
        return true;

    }
    bool Map::setShipUsingXandY(Ship *ship, int x, int y, int director){
        switch(director){
            case 0:{
                if(checkUp(x,y, ship->length)){
                    for(int i=1; i<ship->length; ++i){
                        fieldsStatus[x-i][y]=1;
                        grid[x-i][y]=ship;
                    }
                    return true;
                }
                return false;
            }
            case 1:{
                if(checkRight(x,y,ship->length)){
                    for(int i=1; i<ship->length; ++i){
                        fieldsStatus[x][y+i]=1;
                        grid[x][y+i]= ship;
                    }
                    return true;
                }
                return false;
            }
            case 2:{
                if(checkDown(x,y,ship->length)){
                    for(int i=1; i<ship->length; ++i){
                        fieldsStatus[x+i][y]=1;
                        grid[x+i][y]= ship;
                        
                    }
                    return true;
                }
                return false;
            }
            case 3:{
                if(checkLeft(x,y,ship->length)){
                    for(int i=1; i<ship->length; ++i){
                        fieldsStatus[x][y-i]=1;
                        grid[x][y-i]= ship;
                    }
                    return true;
                }
                return false;
            }
            default:
                return false;
        }

        return false;
    }
    bool Map::setFirstPartOfShip(Ship *ship, int x, int y){
        if(fieldsStatus[x][y]==0 &&
            (fieldsStatus[x-1][y]==0 || fieldsStatus[x-1][y]==-1) &&
            (fieldsStatus[x+1][y]==0 || fieldsStatus[x+1][y]==-1) &&
            (fieldsStatus[x][y-1]==0 || fieldsStatus[x][y-1]==-1) &&
            (fieldsStatus[x][y+1]==0 || fieldsStatus[x][y+1]==-1)){
            fieldsStatus[x][y]=1;
            grid[x][y]=ship;
            return true;
        }
            return false;
    }
    void Map::clearPlace(int x,int y){
        if(x>0 && x<11 && y>0 && y<11)
        fieldsStatus[x][y]=0;
        grid[x][y]=NULL;
    }  
    void Map::clearMap(){
        memset(grid, 0, 144*sizeof(int));
        memset(fieldsStatus, 0, 144*sizeof(int));
        for(int i=0; i<12; i++){
            fieldsStatus[0][i]=-1;
            fieldsStatus[11][i]=-1;
            fieldsStatus[i][0]=-1;
            fieldsStatus[i][11]=-1;
        }
    }
