/*! \file player.cpp
    \brief Zawiera definicje metod klasy Player
*/
#include "player.hpp"
    //! Konstruktor
    /*!
        Inicjuje pola klasy wartosciami
    */
    Player::Player(){
        lifePoints = 0;
        mode = SPREAD;
        currentShip = NULL;
    }
    //! Metoda ustawiajaca nazwe
    /*!
        \param name nazwa do ustawienia
    */
    void Player::setName(std::string name){
        this->name = name;
    }
    //! Destruktor
    /*!
        Usuwa wskazniki z listy wskaznikow na statek
    */
    Player::~Player(){
        for(std::list<Ship*>::iterator it = listOfShips.begin(); it!=listOfShips.end(); it++){
            delete *it;
        }
    }
    //! Metoda tworzaca statki gracza
    /*!
        \param two ilosc statkow dwu polowych
        \param three ilosc statkow trzy polowych
        \param four ilosc statkow czteropolowych
    */
    void Player::createShips(int two, int three, int four){
        int x = 410;
        int y = 180;
        for(int j=0; j<two; j++){
            Ship* player_ship=new Ship(2);
            try{
                if(!player_ship) throw "Error during creation of ship(2)! Application will close in";
            } catch (const char *err){
                sf::RenderWindow exception_window;
                exception_window.create(sf::VideoMode(600, 200, 60), "Critical error!", sf::Style::Close);
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
            player_ship->isPlaced = NOTPLACED;
            player_ship->X = x;
            player_ship->Y = y;
            y=y+2*40+15;
        }
        y = 180;
        x += 50;
        for(int j=0; j<three; j++){
            Ship* player_ship=new Ship(3);
            try{
                if(!player_ship) throw "Error during creation of ship(3)! Application will close in";
            } catch (const char *err){
                sf::RenderWindow exception_window;
                exception_window.create(sf::VideoMode(600, 200, 60), "Critical error!", sf::Style::Close);
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
            player_ship->isPlaced = NOTPLACED;
            player_ship->X = x;
            player_ship->Y = y;
            y = y+3*40 + 15;

        }
        y = 180;
        x += 50;
        for(int j=0; j<four; j++){
            Ship* player_ship=new Ship(4);
            try{
                if(!player_ship) throw "Error during creation of ship(4)! Application will close in";
            } catch (const char *err){
                sf::RenderWindow exception_window;
                exception_window.create(sf::VideoMode(600, 200, 60), "Critical error!", sf::Style::Close);
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
            player_ship->isPlaced = NOTPLACED;
            player_ship->X = x;
            player_ship->Y = y;
            y = y+4*40 + 15;
        }
    }
    //! Metoda resetujaca pola zajete przez gracza
    void Player::resetLifePoints(){
        lifePoints = 0;
        for(std::list<Ship*>::iterator it = listOfShips.begin(); it!=listOfShips.end(); it++){
                this->lifePoints = this->lifePoints + (*it)->length;
        }
    }
    //! Przeksztalca wspolrzedne myszki na wspolrzedne mapy
    /*!
        \param x wspolrzedna x
        \param y wpolrzedna y
        \return zwraca pare nowych wpolrzednych
    */
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
    //! Metoda pozwalajaca strzelac graczowi
    /*!
        \param enemyMap wskaznik na mape przeciwnika
        \return true gdy trafienie
        \return false gdy pudlo
    */
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
    //! Metoda ustawiajaca statki gracza w losowych miejscach
    /*!
        \param playerMap wskaznik na mape gracza
        \return true gdy gdy udalo sie ustawic
    */
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
    //! Metoda wyswietlajaca statki gracza
    /*!
        \param window obiekt glownego okna gry
    */
    void Player::printAllShips(sf::RenderWindow &window){
        sf::Texture destroyedPlayer, ship, destroyedEnemy;
        try{
            if(!destroyedPlayer.loadFromFile("pictures/destroyedPartShip.png")) throw "Error during loading destroyedPartShip.png! Application will close in";
            if(!destroyedEnemy.loadFromFile("pictures/destroyedEnemyPartShip.png")) throw "Error during loading destroyedEnemyPartShip.png! Application will close in";
            if(!ship.loadFromFile("pictures/ShipField.png")) throw "Error during loading ShipField.png! Application will close in";
            } catch (const char *err){
                sf::RenderWindow exception_window;
                exception_window.create(sf::VideoMode(600, 200, 60), "Critical error!", sf::Style::Close);
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
    //! Metoda wyswietlaja wybrany statek
    /*!
        \param window obiekt glownego okna
        \param horizontal wpolrzedna x
        \param vertical wspolrzedna y
    */
    void Player::printChosenShip(sf::RenderWindow &window, int horizontal, int vertical){
        sf::Texture destroyedPlayer, ship, destroyedEnemy;
        try{
            if(!destroyedPlayer.loadFromFile("pictures/destroyedPartShip.png")) throw "Error during loading destroyedPartShip.png! Application will close in";
            if(!destroyedEnemy.loadFromFile("pictures/destroyedEnemyPartShip.png")) throw "Error during loading destroyedEnemyPartShip.png! Application will close in";
            if(!ship.loadFromFile("pictures/ShipField.png")) throw "Error during loading ShipField.png! Application will close in";
            } catch (const char *err){
                sf::RenderWindow exception_window;
                exception_window.create(sf::VideoMode(600, 200, 60), "Critical error!", sf::Style::Close);
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
    //! Metoda zmieniajac stan statku
    /*!
        \param x wspolrzedna x statku
        \param y wspolrzedna y statku
    */
    void Player::changeShipStatus(int x, int y){
        for(std::list<Ship*>::iterator it=listOfShips.begin(); it!=listOfShips.end(); it++){
            if(x>(*it)->X && x<((*it)->X+40) && y>(*it)->Y && y<((*it)->Y+40) && !isSelected && (*it)->isPlaced==NOTPLACED){
                (*it)->isPlaced = DURING;
                isSelected = true;
                currentShip = *it;
            }
        }
    }
    //! Metoda zmieniajaca kierunek statku
    void Player::changeDirection(){
        if(currentShip->isPlaced==DURING){
            currentShip->dir = (currentShip->dir+1)%4;
        }
    }
    //! Metoda sprawdzajaca czy w danym miejscu mozna rozmiescic statek
    /*!
        \param map wskaznik na mape
        \param x wspolrzedna x poczatku statku
        \param y wspolrzedna y poczatku statku
        \return false gdy sie nie udalo
        \return true gdy sie udalo
    */
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
    //! Metoda przerywajaca rozmieszczanie wybranego statku
    void Player::cancelAddingShip(){
        currentShip->isPlaced=NOTPLACED;
        currentShip->dir = dDown;
        isPossible = false;
        isSelected = false;
        currentShip = NULL;
    }
    //! Metoda sprawdzajaca czy wszystkie statki zostaly rozmieszczone
    /*!
        \return true gdy wszsytkie statki zostaly rozmieszczone
        \return false gdy nie wszystkie statki sa rozmieszczone
    */
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
    //! Metoda resetujaca stan wszystkich statkow
    void Player::resetAllShips(){
        for(std::list<Ship*>::iterator it = listOfShips.begin(); it!=listOfShips.end(); ++it){
            (*it)->dir = dDown;
            (*it)->isPlaced = NOTPLACED;
        }
    }
