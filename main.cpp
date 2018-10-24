#include <iostream>
#include <cstdio>

using namespace std;
class ship{
public:
    int row1, row2, row3, col1, col2, col3;
    int hit_count;
    void setship(int row1, int row2, int row3, int col1, int col2, int col3, int playermap[][10]){
        this->row1=row1;
        this->row2=row2;
        this->row3=row3;
        this->col1=col1;
        this->col2=col2;
        this->col3=col3;
        this->hit_count=3;
        playermap[row1][col1]=1;
        playermap[row2][col2]=1;
        playermap[row3][col3]=1;
    }
};
void print_map(int playermap[10][10]){
    cout<<"    ";
    for(int i=0;i<10;i++)
        cout<<"["<<i<<"] ";
    for(int i=0;i<10;i++){
        cout<<"\n";
        cout<<"["<<i<<"]";
        for(int j=0;j<10;j++){
            if(playermap[i][j]==-1) cout <<" [ ]";
            else cout<<" ["<<playermap[i][j]<<"]";
        }

    }
}
void print_map(int playermap[][10], int enemymap[10][10]){
    cout<<"    ";
    for(int i=0;i<10;i++)
        cout<<"[ "<<i<<"] ";
    for(int i=0;i<10;i++){
        cout<<"\n";
        cout<<"["<<i<<"]";
        for(int j=0;j<10;j++){
            if(enemymap[i][j]==-1 || enemymap[i][j]==1)
                cout<<" [ ?]";
            else
                cout<<" ["<<enemymap[i][j]<<"]";
        }

    }
       cout<<"    ";
    for(int i=0;i<10;i++)
        cout<<"[ "<<i<<"] ";
    for(int i=0;i<10;i++){
        cout<<"\n";
        cout<<"["<<i<<"]";
        for(int j=0;j<10;j++){
            cout<<" ["<<playermap[i][j]<<"]";
        }

    }
}
int check_up(int row, int col, int playermap[][10]){
    if(row-1<0)
        return 1;
    else if(playermap[row-1][col]!=1)
        return 1;
    else return 0;
}
int check_down(int row, int col, int playermap[][10]){
    if(row+1>9)
        return 1;
    else if(playermap[row+1][col]!=1)
        return 1;
    else return 0;
}
int check_left(int row, int col, int playermap[][10]){
    if(col-1>=0 && playermap[row][col-1]!=1)
        return 1;
    else return 0;
}
void place_ship(int playermap[][10], ship & ship){
    int row,col=0;
    string direction;
    cout<<"\nRozmieszczanie czterech statkow o dlugosci 3"<<endl;
    print_map(playermap);
    while(1){
        cout<<"\nPodaj wpolrzedne poczatku statku (wiersz,kolumna), oraz gdzie ma byc skierowany (gora, dol, lewo, prawo)"<<endl;
        cin>>row;
        cin>>col;
        cin>>direction;
        if(playermap[row][col]==-1 && direction=="gora")
            if((((row-1)>=0 && playermap[row-1][col]!=1)&&((row-2)>=0 && playermap[row-2][col]!=1)) && check_up(row-2, col, playermap)){
                ship.setship(row, row-1, row-2, col, col , col, playermap);
                break;
            }
        if(playermap[row][col]==-1 && direction=="dol")
            if((((row+1)<=9 && playermap[row+1][col]!=1)&&((row+2)<=9 && playermap[row+2][col]!=1)) && check_down(row+2, col, playermap)){
                ship.setship(row, row+1, row+2, col, col , col, playermap);
                break;
            }
        if(playermap[row][col]==-1 && direction=="lewo")
            if((((col-1)>=0 && playermap[row][col-1]!=1)&&((col-2)>=0 && playermap[row][col-2]!=1))){
                ship.setship(row, row, row, col, col-1, col-2, playermap);
                break;
            }
        if(playermap[row][col]==-1 && direction=="prawo")
            if(((col+1)<=9 && playermap[row][col+1]!=1)&&((col+2)<=9 && playermap[row][col+2]!=1)){
                ship.setship(row, row, row, col, col+1, col+2, playermap);
                break;
            }
        cout<<"Na ktoryms z pol juz znajduje sie statek lub zakres wykracza poza mape"<<endl;
    }

}
int main(){
    int playermap[10][10];
    int enemymap[10][10];
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            playermap[i][j]=-1;
            enemymap[i][j]=-1;
        }
    }
    ship player_ship1;
    ship player_ship2;
    ship player_ship3;
    ship player_ship4;
    place_ship(playermap, player_ship1);
    place_ship(playermap, player_ship2);
    place_ship(playermap, player_ship3);
    place_ship(playermap, player_ship4);
    print_map(playermap);
    return 0;
}
