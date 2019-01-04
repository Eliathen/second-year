/*! \file enemy.cpp
    \brief Zawiera definicje metod klasy Enemy
*/
#include "enemy.hpp"
    //! Konstruktor
    /*!
        \param name nazwa przeciwnika
        Zainicjowanie pol klasy wartosciami
    */
    Enemy::Enemy(std::string name){
        this->name = name;
        lifePoints = 0;
        prevHit = false;
    }
    //! Destruktor
    /*!
        Usuwa wkazniki na statek  z listy wskaznikow
    */
    Enemy::~Enemy(){
            for(std::list<Ship*>::iterator it = listOfShips.begin(); it!=listOfShips.end(); it++){
                delete *it;
            }
    }
    //! Metoda tworzaca statki o dlugosci 2,3 oraz 4 pola i dodajaca je do listy
    /*!
        \param two ilosc statkow dwu polowych
        \param three ilosc statkow trzy polowych
        \param four ilosc statkow cztero polowych
    */
    void Enemy::createShips(int two, int three, int four){
        for(int j=0; j<two; j++){
            Ship* player_ship=new Ship(2);
            try{
                if(!player_ship) throw "Error during creation of ship (2)! Application will close in";
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
            listOfShips.push_back(player_ship);
            lifePoints=lifePoints+player_ship->hitPoints;
            player_ship->isPlaced = 0;
            player_ship->X = 0;
            player_ship->Y = 0;
        }
        for(int j=0; j<three; j++){
            Ship* player_ship=new Ship(3);
            try{
                if(!player_ship) throw "Error during creation of ship (3)! Application will close in";
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
            listOfShips.push_back(player_ship);
            lifePoints=lifePoints+player_ship->hitPoints;
            player_ship->isPlaced = 0;
            player_ship->X = 0;
            player_ship->Y = 0;
        }
        for(int j=0; j<four; j++){
            Ship* player_ship=new Ship(4);
            try{
                if(!player_ship) throw "Error during creation of ship (4)! Application will close in";
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
            listOfShips.push_back(player_ship);
            lifePoints=lifePoints+player_ship->hitPoints;
            player_ship->isPlaced = 0;
            player_ship->X = 0;
            player_ship->Y = 0;
        }
    }
    //! Metoda zerujaca punkty zycia danego statku
    void Enemy::resetLifePoints(){
        lifePoints = 0;
        for(std::list<Ship*>::iterator it = listOfShips.begin(); it!=listOfShips.end(); it++){
                this->lifePoints = this->lifePoints + (*it)->length;
        }
    }
    //! Metoda ustawiajaca statek na mapie
    /*!
        \param enemyMap wkaznik na mape przeciwnika
    */
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
    //! Metoda pozwalajaca przeciwnikowi strzelac do mapy gracza
    /*!
        \param playerMap wskaznik na mape gracza
        \return zwraca trafione pole
    */
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
    //! Metoda strzelania w pole bedace nad polem trafionym poprzednio
    /*!
        \param playerMap wskaznik na mape gracza
        \return 0 przy braku trafienia
        \return 1 przy trafieniu
        \return 2 przy trafieniu w trafione juz wczesniej pole
    */
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
    //! Metoda strzelania w pole bedace pod polem trafionym poprzednio
    /*!
        \param playerMap wskaznik na mape gracza
        \return 0 przy braku trafienia
        \return 1 przy trafieniu
        \return 2 przy trafieniu w trafione juz wczesniej pole
    */
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
    //! Metoda strzelania w pole bedace na lewo od pola trafionego poprzednio
    /*!
        \param playerMap wskaznik na mape gracza
        \return 0 przy braku trafienia
        \return 1 przy trafieniu
        \return 2 przy trafieniu w trafione juz wczesniej pole
    */
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
    //! Metoda strzelania w pole bedace na prawo od pola trafionego poprzednio
    /*!
        \param playerMap wskaznik na mape gracza
        \return 0 przy braku trafienia
        \return 1 przy trafieniu
        \return 2 przy trafieniu w trafione juz wczesniej pole
    */
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
    //! Metoda strzelania jezeli poprzedni strzal byl pudlem
    /*!
        \param playerMap wskaznik na mape gracza
        \return 0 przy braku trafienia
        \return 1 przy trafieniu
    */
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
