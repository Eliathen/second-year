#ifndef PLAYERCLASS_H_INCLUDED
#define PLAYERCLASS_H_INCLUDED
#include <fstream>

class player{
public:
    int points;
    int fields;
    std::string name;
    void setname(std::string name){
        this->points=0;
        this->name=name;
    }
    void place_ship_on_map(ship* playermap[][10], ship* ship, int length, map_printer & map_printer){
        ship->setowner("player");
        int row,col=0;
        bool done=false;
        std::string direction;
        comm::setting_ship_of_length(length); //komunikat
        map_printer.print_map(playermap);
        comm::give_set_coords(); //komunikat
        while(!done){
                std::cin>>row;
                std::cin>>col;
                std::cin>>direction;
                done=ship->placeship(playermap, row, col, direction, length, ship);
                if(!done) comm::error_wrong_set_coords(); //komunikat
            }
        }
    void random_place_ship_on_map(ship* playermap[][10], ship* ship, int length){
        ship->setowner("player");
        int row,col=0;
        bool done=false;
        std::string direction;
        int dir;
        while(!done){
                dir=rand()%4;
                if(dir==0)
                    direction="gora";
                if(dir==1)
                    direction="dol";
                if(dir==2)
                    direction="lewo";
                if(dir==3)
                    direction="prawo";
                row=rand()%10;
                col=rand()%10;
                done=ship->placeship(playermap, row, col, direction, length, ship);
            }
        }

    void shoot(ship* enemymap[][10]){
        int row,col;
        row=col=-1;
        comm::give_shoot_coords(); //komunikat
        while(1){
            std::cin>>row;
            std::cin>>col;
            if(row<0 || row>9 || col<0 || col>9)
                comm::error_wrong_shoot_coords(); //komunikat
            else break;
        }
        if((int)enemymap[row][col]!=-2 &&(int)enemymap[row][col]!=-1 && (int)enemymap[row][col]!=0){
            int tmppoints=enemymap[row][col]->get_damage();
            this->points+=tmppoints;
            enemymap[row][col]=(ship *)-2;
            comm::hit(); //komunikat
            }
        else {
            enemymap[row][col]=(ship *)-0;
            comm::miss(); //komunikat
            }
        }
    void count_fields(ship* gamemap[][10]){
        this->fields=0;
        for(int i=0;i<10;i++)
            for(int j=0;j<10;j++)
                if((int)gamemap[i][j]!=-2 && (int)gamemap[i][j]!=-1 && (int)gamemap[i][j]!=0) fields++;
    }
    void save_points(){
        std::ofstream scores;
        scores.open("scores", std::ios::out|std::ios::app);
        scores<<name<<std::endl;
        scores<<points<<std::endl;
        scores.close();
    }
    void load_points(){
        std::ifstream scores;
        std::string name;
        int points;
        scores.open("scores");
        while(!scores.eof()){
            scores>>name;
            scores>>points;
            comm::score(name, points); //komunikat
        }
        scores.close();
    }
};


#endif // PLAYERCLASS_H_INCLUDED
