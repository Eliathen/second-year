#ifndef MAP_PRINTERCLASS_H_INCLUDED
#define MAP_PRINTERCLASS_H_INCLUDED

class map_printer{
public:
    void print_map(ship* playermap[][10]){
    std::cout<<"    ";
    for(int i=0;i<10;i++)
        std::cout<<"["<<i<<"] ";
    for(int i=0;i<10;i++){
        std::cout<<"\n";
        std::cout<<"["<<i<<"]";
        for(int j=0;j<10;j++){
            if((int)playermap[i][j]==-2) comm::print_X(); //komunikat
            if((int)playermap[i][j]==-1) comm::print_blank(); //komunikat
            if((int)playermap[i][j]==0) comm::print_0(); //komunikat
            if((int)playermap[i][j]!=-2 && (int)playermap[i][j]!=-1 && (int)playermap[i][j]!=0) comm::print_1(); //komunikat
            }
        }
    }

    void print_map(ship* playermap[][10], ship* enemymap[][10], int enemyfields, int playerfields, std::string player){
        comm::enemy_map(); //komunikat
        for(int i=0;i<10;i++)
            std::cout<<"["<<i<<"] ";
        for(int i=0;i<10;i++){
            std::cout<<"\n";
            std::cout<<"["<<i<<"]";
            for(int j=0;j<10;j++){
                if((int)enemymap[i][j]==-2) comm::print_X(); //komunikat
                if((int)enemymap[i][j]==-1) comm::print_blank(); //komunikat
                if((int)enemymap[i][j]==0) comm::print_0(); //komunikat
                if((int)enemymap[i][j]!=-2 && (int)enemymap[i][j]!=-1 && (int)enemymap[i][j]!=0) comm::print_blank(); //komunikat
            }
        }
        comm::enemy_controlled_fields(enemyfields); //komunikat
        comm::player_map(); //komunikat
        for(int i=0;i<10;i++)
            std::cout<<"["<<i<<"] ";
        for(int i=0;i<10;i++){
            std::cout<<"\n";
            std::cout<<"["<<i<<"]";
            for(int j=0;j<10;j++){
                if((int)playermap[i][j]==-2) comm::print_X(); //komunikat
                if((int)playermap[i][j]==-1) comm::print_blank(); //komunikat
                if((int)playermap[i][j]==0) comm::print_0(); //komunikat
                if((int)playermap[i][j]!=-2 && (int)playermap[i][j]!=-1 && (int)playermap[i][j]!=0) comm::print_1(); //komunikat
            }
        }
        comm::player_controlled_fields(player, playerfields); //komunikat
    }

};


#endif // MAP_PRINTERCLASS_H_INCLUDED
