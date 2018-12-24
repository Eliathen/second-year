#include "game.hpp"
    Game::Game() {
        window.create(sf::VideoMode(960, 720, 60), "BattleShips!", sf::Style::Close);
        playerMap = new Map("Gracz");
        enemyMap = new Map("AI");
        AI = new Enemy("AI");
        Gamer = new Player();
        AI->createShips(4,3,2);
        Gamer->createShips(4,3,2);
        setMenuOptions();
        font.loadFromFile("pictures/arial.ttf");
        menuStatus = 0;
        Gamer->mode = 0;
        
    }
    Game::~Game(){
        delete Gamer;
        delete AI;
        delete enemyMap;
        delete playerMap;
    }

    void Game::startGame(){
        Gamer->setName("Gracz");
        sf::Texture gameTexture;
        gameTexture.loadFromFile("pictures/gamemap.bmp");
        sf::Texture menuTexture;
        sf::Sprite gameBackground;
        sf::Sprite menuBackground;
        menuTexture.loadFromFile("pictures/menu.bmp");
        gameBackground.setTexture(gameTexture);
        menuBackground.setTexture(menuTexture);
        sf::Texture blankTexture;
        blankTexture.loadFromFile("pictures/clearBackground.bmp");
        sf::Sprite blankSprite;
        blankSprite.setTexture(blankTexture);
        sf::Vector2i position;
        sf::Texture resetTexture;
        resetTexture.loadFromFile("pictures/reset.png");
        sf::Sprite reset;
        reset.setTexture(resetTexture);
        std::string getNick;
        int status=1; //1 pobieranie wspolrzednych po kliknieciu
        bool shipStatus = false;
        bool firstFieldStatus=false;
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
                if(event.type == sf::Event::MouseButtonPressed){
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        position = sf::Mouse::getPosition(window);
                        if((menuStatus == staticSpread || menuStatus == autoSpread) && status==1){//status pobierania wspolrzednych
                            position = sf::Mouse::getPosition(window);
                            cell = Gamer->getCoordinate(position.x, position.y);
                            status = 3;//status dodawania 1 masztu/atak;
                        }
                    }
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                        if(menuStatus==staticSpread){
                            playerMap->clearPlace(std::get<0>(cell), std::get<1>(cell));
                            status = 1;
                            showGame(gameBackground);
                        }
                    }
                }
                if(event.type == sf::Event::KeyPressed){
                    switch(event.key.code){
                        case sf::Keyboard::Escape://Problem!
                            if(menuStatus!=menu){
                                menuStatus=menu;
                                position.x=position.y = 0;
                                Gamer->mode = 0;
                            }
                            break;

                        case sf::Keyboard::Up:
                            if(menuStatus == staticSpread && status==2){//status pobierania kierunku
                                Gamer->direction = 0;
                                status = 4;//Dodany pierwszy maszt statku i pobrany kierunek
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
                    std::string tekst = "Ustawiasz statek o dlugosci "+std::to_string(((*it)->length))+" Wybierz pole na ktorym chcesz umiescic statek!";
                    printStatment(tekst);
                    showGame(gameBackground);
                }
                else if(position.x>210 && position.x <760 && position.y>255 && position.y <305){
                    newGame();
                    menuStatus = autoSpread;
                    playerMap->clearMap();
                    enemyMap->clearMap();
                    AI->placeShips(enemyMap);
                    showGame(gameBackground);
                }
                else if(position.x>210 && position.x <760 && position.y>410 && position.y <460){
                    menuStatus = instruction;
                    showInstruction(blankSprite);

                }
                else if(position.x>210 && position.x <760 && position.y>565 && position.y <615){
                    window.close();
                }
            } 
            if(menuStatus == instruction){
                    showInstruction(blankSprite);

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
            if(menuStatus==staticSpread && it!=Gamer->listOfShips.end()){
                while(it!=Gamer->listOfShips.end() && menuStatus == staticSpread && Gamer->mode == 0 && status!=1 && status !=2){//Umieszczanie statków użytkownika
                    if(!(position.x>34 && position.x<400 && position.y>167 && position.y<538) && std::get<0>(cell)>0 && std::get<1>(cell)) 
                        {
                            status = 1;
                            //std::string tekst = "Ustawiasz statek o dlugosci "+std::to_string(((*it)->length))+" Wybierz pole na ktorym chcesz umiescic statek!";
                            //printStatment(tekst);
                            
                        }
                    if(status == 3){//mozna ustawic 1 pole
                        firstFieldStatus = playerMap->setFirstPartOfShip(*it, std::get<0>(cell), std::get<1>(cell));
                        if(!firstFieldStatus){
                            status = 1;
                           // std::string tekst = "Ustawiasz statek o dlugosci "+std::to_string(((*it)->length))+" Wybierz pole na ktorym chcesz umiescic statek!";
                           // printStatment(tekst);
                        }
                        else{
                            status = 2;
                            std::string tekst = "Wybierz kierunek w ktorym chcesz ustawic statek.";
                            printStatment(tekst);
                        } 
                    showGame(gameBackground);
                    }
                    if(Gamer->direction >=0 && Gamer->direction <4 && firstFieldStatus == true && status == 4){//
                            shipStatus = playerMap->setShipUsingXandY(*it, std::get<0>(cell), std::get<1>(cell), Gamer->direction);
                            if(shipStatus){
                                std::get<0>(cell)=std::get<1>(cell)=0;
                                status = 1;
                                //std::string tekst = "Ustawiasz statek o dlugosci "+std::to_string(((*it)->length))+" Wybierz pole na ktorym chcesz umiescic statek!";
                                 //   printStatment(tekst);
                                it++;
                            }
                            else{
                                status = 2;
                            }

                    }
                    if(it!=Gamer->listOfShips.end() && status == 1){
                        std::string tekst = "Ustawiasz statek o dlugosci "+std::to_string(((*it)->length))+" Wybierz pole na ktorym chcesz umiescic statek!";
                            printStatment(tekst);
                    }
                    else if(it==Gamer->listOfShips.end()){
                        printStatment("Pora na Atak! Twoja tura: ");
                    }
                    showGame(gameBackground);
                }
            }       
            if(it==Gamer->listOfShips.end() && shipStatus == true && Gamer->mode == 0){
                Gamer->mode = 1;
                position.x = position.y = 0;
                status = 1;
            }
            while((AI->lifePoints!=0 && Gamer->lifePoints!=0) && Gamer->mode == 1 && status == 3){//atack
                if(!(position.x>560 && position.x<920 && position.y>168 && position.y<540)) 
                {
                    status = 1;
                }
                bool playersTurn=true;
                int enemysTurn = 0;
                    while(playersTurn){
                        if(status==3){
                            playersTurn = Gamer->playerAttack(enemyMap, std::get<0>(cell), std::get<1>(cell));
                            if(playersTurn){
                                (AI->lifePoints)--;
                                status = 1;
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
                            playersTurn=false; 
                            status = 1;
                            printStatment("Twoja tura: ");
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
                    if(Gamer->lifePoints==0){//Problem z wyswietleniem kolejnego zwyciestwa/porazki
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
                it = Gamer->listOfShips.begin();
                shipStatus = false;
                firstFieldStatus=false;
                status = 1;
                newGame();
                if(menuStatus==staticSpread){
                    std::string tekst = "Ustawiasz statek o dlugosci "+std::to_string(((*it)->length))+" Wybierz pole na ktorym chcesz umiescic statek!";
                    printStatment(tekst);
                }
                showGame(gameBackground);
            }
       }
    
    }
    void Game::showGame(sf::Sprite gameBackground){
            window.clear(sf::Color::White); 
            window.draw(gameBackground);
            window.draw(text);
            playerMap->printMap(window);
            enemyMap->printMap(window);
            window.display();

    }
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
    void Game::printStatment(std::string statment){
        text.setString(statment);
        text.setFont(font);
        text.setCharacterSize(23);
        text.setPosition(60,665);
        text.setFillColor(sf::Color::Black);

    }
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
    void Game::setMenuOptions(){
        optionInMenu[0]="Nowa Gra (manualnie)";
        optionInMenu[1]="Nowa Gra (automatycznie)";
        optionInMenu[2]="Instrukcja";
        optionInMenu[3]="Quit";
    }
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
    void Game::newGame(){
        enemyMap->clearMap();
        playerMap->clearMap();
        textResult.setString("");
        //Zerowanie punktow;
        Gamer->resetLifePoints();
        AI->placeShips(enemyMap);
        AI->resetLifePoints();
        Gamer->mode = 0;
    }
    void Game::downloadInstruction(std::string *inst){
        std::ifstream file;
        std::string tmpstring;
        file.open("instruction.txt");
        if(!file.is_open()){
            //wyjatek
        }
        else{
            while(!file.eof()){
                getline(file, tmpstring);
                *inst+=tmpstring;
                *inst+='\n';
                tmpstring.clear();
            }
            file.close();
        }
    }