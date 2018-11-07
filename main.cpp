//Ver 1.6 (TEST)//

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <list>

#include "commclass.h"
#include "shipclass.h"
#include "enemyclass.h"
#include "map_printerclass.h"
#include "playerclass.h"

int main(){
    srand(time(0));
    int choice;
    int length=2;
    std::list<ship *>list_of_player_ships;
    std::list<ship *>list_of_enemy_ships;
    map_printer map_printer;
    player player;
    enemy enemy;
    std::string name;
    comm::give_name(); //komunikat
    std::cin>>name;
    player.setname(name);
    enemy.sethit();
    while(1){
        comm::menu(); //komunikat
        std::cin>>choice;
        if(choice==1 || choice==2) break;
        else player.load_points();
    }
    ship* playermap[10][10];
    ship* enemymap[10][10];
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            playermap[i][j]=(ship *)-1;
            enemymap[i][j]=(ship *)-1;
        }
    }
    for(int i=0;i<9;i++){
        ship* player_ship=new ship;
        ship* enemy_ship=new ship;
        list_of_player_ships.push_back(player_ship);
        list_of_enemy_ships.push_back(enemy_ship);
        player_ship=enemy_ship=0;
        delete player_ship;
        delete enemy_ship;
    }
    std::list<ship*>::iterator it;
    int i=0;
    for(it=list_of_player_ships.begin();it!=list_of_player_ships.end();++it){
        if(i==4 || i==7) length++;
        if(choice==1){
            player.place_ship_on_map(playermap, *it, length, map_printer);
            i++;
        }
        if(choice==2){
            player.random_place_ship_on_map(playermap, *it, length);
            i++;
        }
    }
    i=0;
    length=2;
    for(it=list_of_enemy_ships.begin();it!=list_of_enemy_ships.end();++it){
        if(i==4 || i==7) length++;
        enemy.place_ship_on_map(enemymap, *it, length);
        i++;
    }

    player.count_fields(playermap);
    enemy.count_fields(enemymap);
    map_printer.print_map(playermap, enemymap, enemy.fields, player.fields, name);
    while(1){
        player.shoot(enemymap);
        enemy.count_fields(enemymap);
        if(enemy.fields==0) {comm::game_over("win", player.points); break;} //komunikat
        enemy.shoot(playermap);
        player.count_fields(playermap);
        if(player.fields==0) {comm::game_over("lose", player.points); break;} //komunikat
        map_printer.print_map(playermap, enemymap, enemy.fields, player.fields, name);
    }
    player.save_points();
    for(it=list_of_player_ships.end();it!=list_of_player_ships.begin();++it){
        list_of_player_ships.erase(it);
        delete *it;
    }
    for(it=list_of_enemy_ships.end();it!=list_of_enemy_ships.begin();++it){
        list_of_enemy_ships.erase(it);
        delete *it;
    }
    return 0;
}
