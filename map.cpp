/*! \file map.cpp
    \brief Zawiera definicje metod klasy Map
*/
#include "map.hpp"
    //! Konstruktor
    /*!
        \param nazwa nazwa wlasciciela mapy
        Inicjuje pola wartosciami
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
    //! Destruktor
    Map::~Map(){
    }
    //! Metoda wyswietlajaca mape
    /*!
        \param window obiekt glownego okna gry
    */
    void Map::printMap(sf::RenderWindow &window){
        sf::Texture empty, destroyedPlayer, ship, miss, destroyedEnemy;
        try{
            if(!empty.loadFromFile("pictures/EmptyField.png")) throw "Error during loading EmptyField.png! Application will close in";
            if(!destroyedPlayer.loadFromFile("pictures/destroyedPartShip.png")) throw "Error during loading destroyedPartShip.png! Application will close in";
            if(!destroyedEnemy.loadFromFile("pictures/destroyedEnemyPartShip.png")) throw "Error during loading destroyedEnemyPartShip.png! Application will close in";
            if(!ship.loadFromFile("pictures/ShipField.png")) throw "Error during loading ShipField.png! Application will close in";
            if(!miss.loadFromFile("pictures/missAttack.png")) throw "Error during loading ShipField.png! Application will close in";
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
                        //pole trafione. Bylo puste
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
    //! Metoda sprawdzajaca pola znajdujace sie nad polem poczatku statku
    /*!
        \param row wiersz poczatku statku
        \param col kolumna poczatku statki
        \param len dlugosc statku
        \return false jezeli pola nie sa puste lub wychodza poza obszar gry
        \return true jezeli pola sa puste
    */
    bool Map::checkUp(int row, int col, int len){
        for(int i=0; i<len; ++i){
            if(fieldsStatus[row-i][col]!=0 ||
                (fieldsStatus[row-i+1][col]!=0 && fieldsStatus[row-i+1][col]!=-1)||
                (fieldsStatus[row-i-1][col]!=0 && fieldsStatus[row-i-1][col]!=-1)||
                (fieldsStatus[row-i][col+1]!=0 && fieldsStatus[row-i][col+1]!=-1)||
                (fieldsStatus[row-i][col-1]!=0 && fieldsStatus[row-i][col-1]!=-1)){
                return false;
            }
        }
        return true;

    }
    //! Metoda sprawdzajaca pola znajdujace sie pod polem poczatku statku
    /*!
        \param row wiersz poczatku statku
        \param col kolumna poczatku statki
        \param len dlugosc statku
        \return false jezeli pola nie sa puste lub wychodza poza obszar gry
        \return true jezeli pola sa puste
    */
    bool Map::checkDown(int row, int col, int len){
        for(int i=0; i<len; ++i){
            if(fieldsStatus[row+i][col]!=0 ||
                (fieldsStatus[row+i-1][col]!=0 && fieldsStatus[row+i-1][col]!=-1)||
                (fieldsStatus[row+i+1][col]!=0 && fieldsStatus[row+i+1][col]!=-1)||
                (fieldsStatus[row+i][col-1]!=0 && fieldsStatus[row+i][col-1]!=-1)||
                (fieldsStatus[row+i][col+1]!=0 && fieldsStatus[row+i][col+1]!=-1)){
                return false;
            }
        }
        return true;

    }
    //! Metoda sprawdzajaca pola znajdujace sie na lewo od pola poczatku statku
    /*!
        \param row wiersz poczatku statku
        \param col kolumna poczatku statki
        \param len dlugosc statku
        \return false jezeli pola nie sa puste lub wychodza poza obszar gry
        \return true jezeli pola sa puste
    */
    bool Map::checkLeft(int row, int col, int len){
        for(int i=0; i<len; ++i){
            if(fieldsStatus[row][col-i]!=0 ||
                (fieldsStatus[row-1][col-i]!=0 && fieldsStatus[row-1][col-i]!=-1)||
                (fieldsStatus[row+1][col-i]!=0 && fieldsStatus[row+1][col-i]!=-1)||
                (fieldsStatus[row][col-i-1]!=0 && fieldsStatus[row][col-i-1]!=-1)||
                (fieldsStatus[row][col-i+1]!=0 && fieldsStatus[row][col-i+1]!=-1)
                ){

                return false;
            }

        }
        return true;
    }
    //! Metoda sprawdzajaca pola znajdujace sie na prawo od pola poczatku statku
    /*!
        \param row wiersz poczatku statku
        \param col kolumna poczatku statki
        \param len dlugosc statku
        \return false jezeli pola nie sa puste lub wychodza poza obszar gry
        \return true jezeli pola sa puste
    */
    bool Map::checkRight(int row, int col, int len){
        for(int i=0; i<len; ++i){
            if(fieldsStatus[row][col+i] ||
                (fieldsStatus[row-1][col+i]!=0 && fieldsStatus[row-1][col+i]!=-1)||
                (fieldsStatus[row+1][col+i]!=0 && fieldsStatus[row+1][col+i]!=-1)||
                (fieldsStatus[row][col+i+1]!=0 && fieldsStatus[row][col+i+1]!=-1)||
                (fieldsStatus[row][col+i-1]!=0 && fieldsStatus[row][col+i-1]!=-1)
                ){

                return false;
            }

        }
        return true;

    }
    //! Metoda ustawiajaca statek na mapie
    /*!
        \param ship wskaznik na statek do ustawienia
        \param row wiersz poczatku statku
        \param col kolumna poczatku statku
        \return true jezeli sie udalo
        \return false jezeli sie nie udalo
    */
    bool Map::setShipUsingXandY(Ship *ship, int row, int col){
        switch(ship->dir){
            case 0:{
                if(checkUp(row,col, ship->length)){
                    for(int i=0; i<ship->length; ++i){
                        fieldsStatus[row-i][col]=1;
                        grid[row-i][col]=ship;
                    }
                    return true;
                }
                return false;
            }
            case 1:{
                if(checkRight(row,col,ship->length)){
                    for(int i=0; i<ship->length; ++i){
                        fieldsStatus[row][col+i]=1;
                        grid[row][col+i]= ship;
                    }
                    return true;
                }
                return false;
            }
            case 2:{
                if(checkDown(row,col,ship->length)){
                    for(int i=0; i<ship->length; ++i){
                        fieldsStatus[row+i][col]=1;
                        grid[row+i][col]= ship;

                    }
                    return true;
                }
                return false;
            }
            case 3:{
                if(checkLeft(row,col,ship->length)){
                    for(int i=0; i<ship->length; ++i){
                        fieldsStatus[row][col-i]=1;
                        grid[row][col-i]= ship;
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
    //! Metoda czyszczaca pole z wartosci
    /*!
        \param row wiersz pola
        \param col kolumna pola
        \param len dlugosc statku
    */
    void Map::clearPlace(int row,int col){
        if(row>0 && row<11 && col>0 && col<11)
        fieldsStatus[row][col]=0;
        grid[row][col]=NULL;
    }
    //! Metoda czyszczaca cala mape
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
