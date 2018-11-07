#ifndef COMMCLASS_H_INCLUDED
#define COMMCLASS_H_INCLUDED

class comm{
public:
    static void give_name();
    static void menu();
    static void game_over(std::string n, int points);
    static void setting_ship_of_length(int length);
    static void give_set_coords();
    static void error_wrong_set_coords();
    static void give_shoot_coords();
    static void error_wrong_shoot_coords();
    static void hit();
    static void miss();
    static void score(std::string name, int points);
    static void print_X();
    static void print_0();
    static void print_1();
    static void print_blank();
    static void player_controlled_fields(std::string player, int fields);
    static void enemy_controlled_fields(int fields);
    static void player_map();
    static void enemy_map();
};

void comm::give_name(){
    std::cout<<"Podaj swoje imie"<<std::endl;
}
void comm::menu(){
    std::cout<<"1.Nowa gra(Manualnie)\n2.Nowa gra(Losowo)\n3.Zobacz tablice wynikow"<<std::endl;
}
void comm::game_over(std::string outcome, int points){
    if(outcome=="win")
        std::cout<<"WYGRANA\nTwoje punkty: "<<points;
    if(outcome=="lose")
        std::cout<<"PRZEGRANA!\nTwoje punkty: "<<points;
}
void comm::setting_ship_of_length(int length){
    std::cout<<"\nRozmieszczanie "<<length<<" masztowca"<<std::endl;
}
void comm::give_set_coords(){
    std::cout<<"\nPodaj wpolrzedne poczatku statku (wiersz,kolumna), oraz gdzie ma byc skierowany (gora, dol, lewo, prawo)"<<std::endl;
}
void comm::error_wrong_set_coords(){
    std::cout<<"Na ktoryms z pol juz znajduje sie statek lub zakres wykracza poza mape"<<std::endl;
}
void comm::give_shoot_coords(){
    std::cout<<"\nWybierz cel(wiersz, kolumna)"<<std::endl;
}
void comm::error_wrong_shoot_coords(){
    std::cout<<"Bledne wspolrzedne"<<std::endl;
}
void comm::hit(){
    std::cout<<"Trafienie!"<<std::endl;
}
void comm::miss(){
    std::cout<<"Pudlo!"<<std::endl;
}
void comm::score(std::string name, int points){
    std::cout<<name<<" - "<<points<<std::endl;
}
void comm::print_X(){
    std::cout<<" [X]";
}
void comm::print_0(){
    std::cout<<" [0]";
}
void comm::print_1(){
    std::cout<<" [1]";
}
void comm::print_blank(){
    std::cout<<" [ ]";
}
void comm::player_controlled_fields(std::string player, int fields){
    std::cout<<"Pola zajete przez "<<player<<": "<<fields;
}
void comm::enemy_controlled_fields(int fields){
    std::cout<<"Pola zajete przez przeciwnika: "<<fields;
}
void comm::player_map(){
    std::cout<<"\nMAPA GRACZA\n";
    std::cout<<"    ";
}
void comm::enemy_map(){
    std::cout<<"MAPA PRZECIWNIKA\n";
    std::cout<<"    ";
}
#endif // COMMCLASS_H_INCLUDED
