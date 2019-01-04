/*! \file game.cpp
    \brief Zawiera definicje metod klasy Game
*/
#include "game.hpp"
    //! Konstruktor
    /*!
        Zainicjowanie pol klasy wartosciami
    */
    Game::Game() {
        window.create(sf::VideoMode(960, 720, 60), "BattleShips!", sf::Style::Close);
        playerMap = new Map("Gracz");
        enemyMap = new Map("AI");
        AI = new Enemy("AI");
        Gamer = new Player();
        try{
            if(!Gamer) throw "Error during creation of player! Application will close in";
            if(!AI) throw "Error during creation of AI! Application will close in";
            if(!enemyMap) throw "Error during creation of Enemy map! Application will close in";
            if(!playerMap) throw "Error during creation of Player map! Application will close in";
            } catch (const char *err){
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
        AI->createShips(4,3,2);
        Gamer->createShips(4,3,2);
        setMenuOptions();
        font.loadFromFile("pictures/arial.ttf");
        menuStatus = 0;
        Gamer->mode = 0;

    }
    //! Destruktor
    /*!
        Usuwa wskazniki na obiekty bedace polami klasy game
    */
    Game::~Game(){
        delete Gamer;
        delete AI;
        delete enemyMap;
        delete playerMap;
    }
    //! Glowna metoda kontrolujaca i obslugujaca obecna sesje gry
    void Game::startGame(){
        Gamer->setName("Gracz");
        sf::Texture gameTexture;
        sf::Texture menuTexture;
        sf::Texture blankBackgroundTexture;
        sf::Texture resetTexture;
        try{
            if(!gameTexture.loadFromFile("pictures/gamemap.bmp")) throw "Error during loading gamemap.bmp! Application will close in";
            if(!menuTexture.loadFromFile("pictures/menu.bmp")) throw "Error during loading menu.bmp! Application will close in";
            if(!blankBackgroundTexture.loadFromFile("pictures/clearBackground.bmp")) throw "Error during loading clearBackground.bmp! Application will close in";
            if(!resetTexture.loadFromFile("pictures/reset.png")) throw "Error during loading reset.png! Application will close in";
            } catch (const char *err){
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
        sf::Sprite reset;
        sf::Sprite blankBackgroundSprite;
        sf::Sprite gameBackground;
        sf::Sprite menuBackground;
        gameBackground.setTexture(gameTexture);
        menuBackground.setTexture(menuTexture);
        blankBackgroundSprite.setTexture(blankBackgroundTexture);
        reset.setTexture(resetTexture);
        sf::Vector2i position;
        int status=1;
        bool playersTurn = true;
        int enemysTurn = 0;
        std::list<Ship*>::iterator it = Gamer->listOfShips.begin();
        auto cell = Gamer->getCoordinate(position.x, position.y);
        position.x = position.y = 0;
        while (window.isOpen()){
            sf::Event event;
            while(window.pollEvent(event)){
                if (event.type == sf::Event::Closed){
                    window.close();
                    break;
                }
                if(event.type==sf::Event::MouseMoved){
                    if(menuStatus == staticSpread && Gamer->isSelected){
                        position = sf::Mouse::getPosition(window);
                        //Gamer->isPossible = Gamer->isPossibleToPlace(playerMap, position.x, position.y);
                    }
                }
                if(event.type == sf::Event::MouseButtonReleased){
                    if(event.mouseButton.button == sf::Mouse::Left){
                        if(Gamer->currentShip && Gamer->isPossible==false && Gamer->mode == 0){
                            Gamer->cancelAddingShip();
                        }
                        if(Gamer->currentShip && Gamer->isPossible==true && Gamer->mode == 0){
                            cell = Gamer->getCoordinate(position.x, position.y);
                            playerMap->setShipUsingXandY(Gamer->currentShip, std::get<0>(cell), std::get<1>(cell));
                            Gamer->isSelected = false;
                            Gamer->isPossible = false;
                            Gamer->currentShip->isPlaced = PLACED;
                            Gamer->currentShip = NULL;
                        }

                    }
                }
                if(event.type == sf::Event::MouseButtonPressed){
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        position = sf::Mouse::getPosition(window);
                        if(status == 1 && Gamer->mode ==1){
                            position = sf::Mouse::getPosition(window);
                            status = 3;
                        }
                        if(menuStatus == staticSpread){
                            if(Gamer->isSelected==false){
                                position = sf::Mouse::getPosition(window);
                                Gamer->changeShipStatus(position.x,position.y);
                            }
                            if(Gamer->isSelected==true){
                                position = sf::Mouse::getPosition(window);
                                status = 3;
                            }
                        }
                    }
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                        if(menuStatus==staticSpread && Gamer->isSelected){
                            Gamer->changeDirection();
                        }
                    }
                }
                if(event.type == sf::Event::KeyPressed){
                    switch(event.key.code){
                        case sf::Keyboard::Escape:
                            if(menuStatus!=menu){
                                menuStatus=menu;
                                Gamer->mode = 0;
                                printStatment(" ");
                            }
                            break;

                        case sf::Keyboard::Up:
                            if(menuStatus == staticSpread && status==2){
                                Gamer->direction = 0;
                                status = 4;
                            }
                            break;
                        case sf::Keyboard::Right:
                            if(menuStatus == staticSpread && status==2){
                                Gamer->direction = 1;
                                status = 4;
                            }
                            break;
                        case sf::Keyboard::Down:
                            if(menuStatus == staticSpread && status==2){
                                Gamer->direction = 2;
                                status = 4;
                            }
                            break;
                        case sf::Keyboard::Left:
                            if(menuStatus == staticSpread && status==2){
                                Gamer->direction = 3;;
                                status = 4;
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
            if(menuStatus == menu){
                showMenu(menuBackground);
                if(position.x>210 && position.x < 760 && position.y>100 && position.y < 150){
                    newGame();
                    it = Gamer->listOfShips.begin();
                    menuStatus = staticSpread;
                    playerMap->clearMap();
                    enemyMap->clearMap();
                    AI->placeShips(enemyMap);
                    position.x=position.y = 0;
                }
                else if(position.x>210 && position.x <760 && position.y>255 && position.y <305){
                    newGame();
                    menuStatus = autoSpread;
                    playerMap->clearMap();
                    enemyMap->clearMap();
                    AI->placeShips(enemyMap);
                    showGame(gameBackground);
                    position.x=position.y = 0;
                }
                else if(position.x>210 && position.x <760 && position.y>410 && position.y <460){
                    menuStatus = instruction;
                    showInstruction(blankBackgroundSprite);
                    position.x=position.y = 0;

                }
                else if(position.x>210 && position.x <760 && position.y>565 && position.y <615){
                    window.close();
                }
            }
            if(menuStatus == instruction){
                    showInstruction(blankBackgroundSprite);

            }
            if(menuStatus == autoSpread && Gamer->mode == 0){
                if(!Gamer->placeShipsInRandomPlace(playerMap)){
                    puts("zle umiescilem statki");
                }
                else{
                    Gamer->mode = 1;
                    status = 1;
                    printStatment("Pora na Atak! Twoja tura: ");;
                    showGame(gameBackground);
                }
            }
            if(menuStatus==staticSpread && Gamer->mode ==0){
                showGameDuringStaticSpread(gameBackground, position.x, position.y);
                Gamer->isPossible = Gamer->isPossibleToPlace(playerMap, position.x, position.y);
                Gamer->printChosenShip(window, position.x, position.y);
            }
            if(menuStatus == staticSpread && Gamer->allSet()==true && Gamer->mode == 0){
                Gamer->mode = 1;
                status = 1;
                playersTurn = true;
                position.x = position.y = 0;
                printStatment("Pora na Atak. Twoja tura: ");
                showGame(gameBackground);
            }
            while((AI->lifePoints!=0 && Gamer->lifePoints!=0) && Gamer->mode == 1 && status == 3){//atack
                if(!(position.x>560 && position.x<920 && position.y>168 && position.y<540))
                {
                    status = 1;
                }
                    while(playersTurn && status == 3){
                        if(status==3){
                            cell = Gamer->getCoordinate(position.x, position.y);
                            playersTurn = Gamer->playerAttack(enemyMap, std::get<0>(cell), std::get<1>(cell));
                            if(playersTurn){
                                //jesli trafione
                                (AI->lifePoints)--;
                                status = 1;;
                                enemysTurn = 0;
                            }
                            else{
                                //Jesli pudlo
                                playersTurn=false;
                                enemysTurn = 1;
                                printStatment("Tura przeciwnika: ");
                            }
                        }
                        else{
                            status = 1;
                            playersTurn = true;
                        }
                    showGame(gameBackground);
                    }
                    while(enemysTurn!=0){
                        usleep(700000);
                        enemysTurn = AI->enemyAttack(playerMap);
                        if(enemysTurn==1){
                            (Gamer->lifePoints)--;
                        }
                        if(enemysTurn==0){
                            status = 1;
                            printStatment("Twoja tura: ");
                            playersTurn = true;
                        }
                        showGame(gameBackground);
                    }
                    if(Gamer->lifePoints==0){
                        //YOu lose
                        Gamer->mode = 2;
                        setResult(0);
                        status = 1;
                        position.x = position.y = 0;
                    }
                    if(AI->lifePoints==0){
                        //You winn
                        Gamer->mode = 2;
                        setResult(1);
                        status = 1;
                        position.y = position.x = 0;
                    }
            }
            if(Gamer->mode == 2){
                showGame(gameBackground, reset);
            }
            if(Gamer->mode == 2 &&
                position.x>410 && position.x <510 &&
                position.y>275 && position.y <375){
                position.x = position.y = 0;
                status = 1;
                newGame();
                showGame(gameBackground);
            }
        }

    }
    //! Metoda odswiezajaca okno
    /*!
        \param gameBackground sprite tla gry
    */
    void Game::showGame(sf::Sprite gameBackground){
            window.clear(sf::Color::White);
            window.draw(gameBackground);
            window.draw(text);
            playerMap->printMap(window);
            enemyMap->printMap(window);
            window.display();

    }
    //! Metoda odswiezajaca okno podczas rozstawiania statkow
    /*!
        \param gameBackground sprite tla gry
        \param x wspolrzedna x myszki
        \param y wspolrzedna y myszki
    */
    void Game::showGameDuringStaticSpread(sf::Sprite gameBackground, int x,int y){
            window.clear(sf::Color::White);
            window.draw(gameBackground);
            window.draw(text);
            playerMap->printMap(window);
            enemyMap->printMap(window);
            Gamer->printAllShips(window);
            Gamer->printChosenShip(window, x, y);
            window.display();

    }
    //! Metoda odswiezajaca okno wyswietlajaca napis
    /*!
        \param gameBackground sprite tla gry
        \param reset sprite resetujacy
    */
    void Game::showGame(sf::Sprite gameBackground, sf::Sprite reset){
            window.clear(sf::Color::White);
            window.draw(gameBackground);
            window.draw(text);
            if(Gamer->mode == 2){
                reset.setPosition(410,275);
                reset.scale(0.5,0.5);
                std::string tekst;
                tekst = textResult.getString();;
                window.draw(reset);
                window.draw(textResult);
            }
            playerMap->printMap(window);
            enemyMap->printMap(window);
            window.display();
    }
    //! Metoda ustawiajaca napis
    /*!
        \param statment string do ustawienia
    */
    void Game::printStatment(std::string statment){
        text.setString(statment);
        text.setFont(font);
        text.setCharacterSize(23);
        text.setPosition(60,665);
        text.setFillColor(sf::Color::Black);

    }
    //! Metoda wyswietlajaca wynik w zaleznosci od wygranej lub przegranej
    /*!
        \param result decyduje o wyswietlaja wiadomosci informujacej o wyniku gry
    */
    void Game::setResult(int result){
        font.loadFromFile("pictures/arial.ttf");
        textResult.setFont(font);
        textResult.setCharacterSize(30);
        if(result == 1){
            textResult.setPosition(420, 65);
            textResult.setString("You Win!");
            textResult.setFillColor(sf::Color::Green);
        }
        if(result == 0){
            textResult.setPosition(418, 65);
            textResult.setString("You Lose!");
            textResult.setFillColor(sf::Color::Red);
        }
        else{
        }
    }
    //! Metoda ustawiajaca opcje menu w tablicy
    void Game::setMenuOptions(){
        optionInMenu[0]="New Game (manual)";
        optionInMenu[1]="New Game (automatic)";
        optionInMenu[2]="Instruction";
        optionInMenu[3]="Quit";
    }
    //! Metoda wyswietlajaca menu
    /*!
        \param menuBackground sprite tla menu
    */
    void Game::showMenu(sf::Sprite menuBackground){
        sf::Text menuText[4];
        window.clear(sf::Color::White);
        window.draw(menuBackground);
        int x=230;
        int y=105;
        for(int i = 0; i<4; i++){
            menuText[i].setFont(font);
            menuText[i].setString(optionInMenu[i]);
            menuText[i].setCharacterSize(30);
            menuText[i].setPosition(x,y);
            menuText[i].setFillColor(sf::Color::Black);
            window.draw(menuText[i]);
            y=y+155;
        }
        window.display();
    }
    //! Metoda wyswietlajaca instrukcje do gry
    /*!
        \param blankBackground sprite tla instrukcji
    */
    void Game::showInstruction(sf::Sprite blankBackground){
        window.clear(sf::Color::White);
        window.draw(blankBackground);
        sf::Text instruction;
        instruction.setFont(font);
        std::string inst;
        downloadInstruction(&inst);
        instruction.setString(inst);
        instruction.setCharacterSize(20);
        instruction.setPosition(25, 10);
        instruction.setFillColor(sf::Color::Black);
        window.draw(instruction);
        window.display();
    }
    //! Metoda zaczynajaca nowa gre
    void Game::newGame(){
        enemyMap->clearMap();
        playerMap->clearMap();
        textResult.setString("");
        Gamer->resetLifePoints();
        Gamer->resetAllShips();
        AI->placeShips(enemyMap);
        AI->resetLifePoints();
        Gamer->mode = 0;
    }
    //! Metoda pobierajaca instrukcje z pliku
    /*!
        \param inst wskaznik na string instrukcji do modyfikacji
    */
    void Game::downloadInstruction(std::string *inst){
        std::ifstream file;
        std::string tmpstring;
        file.open("instruction.txt");
        try{
            if(!file.is_open()) throw "Error during opening instruction.txt! Application will close in";
            } catch (const char *err){
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
            while(!file.eof()){
                getline(file, tmpstring);
                *inst+=tmpstring;
                *inst+='\n';
                tmpstring.clear();
            }
            file.close();
        }
