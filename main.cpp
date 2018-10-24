#include <iostream>

using namespace std;

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
class ship2{
public:
    int row1, row2, col1, col2;
    int hit_points;
    void setship(int row1, int row2, int col1, int col2, int playermap[][10]){
        this->row1=row1;
        this->row2=row2;
        this->col1=col1;
        this->col2=col2;
        this->hit_points=2;
        playermap[row1][col1]=1;
        playermap[row2][col2]=1;
    }
    int check_up(int row, int col, int playermap[][10]){
        if(row-1<0)
            return 1;
        else if(playermap[row-1][col]==-1)
            return 1;
        else return 0;
    }

    int check_down(int row, int col, int playermap[][10]){
        if(row+1>9)
            return 1;
        else if(playermap[row+1][col]==-1)
            return 1;
        else return 0;
    }

    int check_left(int row, int col, int playermap[][10]){
        if(col-1<0)
            return 1;
        else if(playermap[row][col-1]==-1)
            return 1;
        else return 0;
    }

    int check_right(int row, int col, int playermap[][10]){
        if(col+1>9)
            return 1;
        else if(playermap[row][col+1]==-1)
            return 1;
        else return 0;
    }

    void placeship(int playermap[][10]){
        int row,col=0;
        string direction;
        cout<<"\nRozmieszczanie dwumasztowca"<<endl;
        print_map(playermap);
        while(1){
            cout<<"\nPodaj wpolrzedne poczatku statku (wiersz,kolumna), oraz gdzie ma byc skierowany (gora, dol, lewo, prawo)"<<endl;
            cin>>row;
            cin>>col;
            cin>>direction;
            if(playermap[row][col]==-1 && direction=="gora")
                if((((row-1)>=0 && playermap[row-1][col]==-1))
                        && check_up(row-1, col, playermap) && check_down(row, col, playermap)
                        && check_left(row , col, playermap) && check_left(row-1, col, playermap)
                        && check_right(row, col, playermap) && check_right(row-1, col, playermap)){
                    setship(row, row-1, col, col , playermap);
                    break;
                }
            if(playermap[row][col]==-1 && direction=="dol")
                if((((row+1)<=9 && playermap[row+1][col]==-1))
                        && check_up(row, col, playermap) && check_down(row+1, col, playermap)
                        && check_left(row , col, playermap) && check_left(row+1, col, playermap)
                        && check_right(row, col, playermap) && check_right(row+1, col, playermap)){
                    setship(row, row+1, col, col , playermap);
                    break;
                }
            if(playermap[row][col]==-1 && direction=="lewo")
                if((((col-1)>=0 && playermap[row][col-1]==-1))
                        && check_left(row, col-1, playermap) && check_right(row, col, playermap)
                        && check_up(row, col, playermap) && check_up(row, col-1, playermap)
                        && check_down(row, col, playermap) && check_down(row, col-1, playermap)){
                    setship(row, row, col, col-1, playermap);
                    break;
                }
            if(playermap[row][col]==-1 && direction=="prawo")
                if(((col+1)<=9 && playermap[row][col+1]==-1)
                        && check_left(row, col, playermap) && check_right(row, col+1, playermap)
                        && check_up(row, col, playermap) && check_up(row, col+1, playermap)
                        && check_down(row, col, playermap) && check_down(row, col+1, playermap)){
                    setship(row, row, col, col+1, playermap);
                    break;
                }
            cout<<"Na ktoryms z pol juz znajduje sie statek lub zakres wykracza poza mape"<<endl;
            }
        }
};

class ship3:public ship2{
public:
    int row3, col3;
    void setship(int row1, int row2, int row3, int col1, int col2, int col3, int playermap[][10]){
        this->row1=row1;
        this->row2=row2;
        this->row3=row3;
        this->col1=col1;
        this->col2=col2;
        this->col3=col3;
        this->hit_points=3;
        playermap[row1][col1]=1;
        playermap[row2][col2]=1;
        playermap[row3][col3]=1;
    }
    void placeship(int playermap[][10]){
        int row,col=0;
        string direction;
        cout<<"\nRozmieszczanie trzymasztowca"<<endl;
        print_map(playermap);
        while(1){
            cout<<"\nPodaj wpolrzedne poczatku statku (wiersz,kolumna), oraz gdzie ma byc skierowany (gora, dol, lewo, prawo)"<<endl;
            cin>>row;
            cin>>col;
            cin>>direction;
            if(playermap[row][col]==-1 && direction=="gora")
                if((((row-1)>=0 && playermap[row-1][col]==-1)&&((row-2)>=0 && playermap[row-2][col]==-1))
                        && check_up(row-2, col, playermap) && check_down(row, col, playermap)
                        && check_left(row , col, playermap) && check_left(row-1, col, playermap) && check_left(row-2, col, playermap)
                        && check_right(row, col, playermap) && check_right(row-1, col, playermap) && check_right(row-2, col, playermap)){
                    setship(row, row-1, row-2, col, col , col, playermap);
                    break;
                }
            if(playermap[row][col]==-1 && direction=="dol")
                if((((row+1)<=9 && playermap[row+1][col]==-1)&&((row+2)<=9 && playermap[row+2][col]==-1))
                        && check_up(row, col, playermap) && check_down(row+2, col, playermap)
                        && check_left(row , col, playermap) && check_left(row+1, col, playermap) && check_left(row+2, col, playermap)
                        && check_right(row, col, playermap) && check_right(row+1, col, playermap) && check_right(row+2, col, playermap)){
                    setship(row, row+1, row+2, col, col , col, playermap);
                    break;
                }
            if(playermap[row][col]==-1 && direction=="lewo")
                if((((col-1)>=0 && playermap[row][col-1]==-1)&&((col-2)>=0 && playermap[row][col-2]==-1))
                        && check_left(row, col-2, playermap) && check_right(row, col, playermap)
                        && check_up(row, col, playermap) && check_up(row, col-1, playermap) && check_up(row, col-2, playermap)
                        && check_down(row, col, playermap) && check_down(row, col-1, playermap) && check_down(row, col-2, playermap)){
                    setship(row, row, row, col, col-1, col-2, playermap);
                    break;
                }
            if(playermap[row][col]==-1 && direction=="prawo")
                if(((col+1)<=9 && playermap[row][col+1]==-1)&&((col+2)<=9 && playermap[row][col+2]==-1)
                        && check_left(row, col, playermap) && check_right(row, col+2, playermap)
                        && check_up(row, col, playermap) && check_up(row, col+1, playermap) && check_up(row, col+2, playermap)
                        && check_down(row, col, playermap) && check_down(row, col+1, playermap) && check_down(row, col+2, playermap)){
                    setship(row, row, row, col, col+1, col+2, playermap);
                    break;
                }
            cout<<"Na ktoryms z pol juz znajduje sie statek lub zakres wykracza poza mape"<<endl;
            }
        }
};

class ship4:public ship3{
public:
    int row4, col4;
    void setship(int row1, int row2, int row3, int row4, int col1, int col2, int col3, int col4, int playermap[][10]){
        this->row1=row1;
        this->row2=row2;
        this->row3=row3;
        this->row4=row4;
        this->col1=col1;
        this->col2=col2;
        this->col3=col3;
        this->col4=col4;
        this->hit_points=3;
        playermap[row1][col1]=1;
        playermap[row2][col2]=1;
        playermap[row3][col3]=1;
        playermap[row4][col4]=1;
    }

    void placeship(int playermap[][10]){
        int row,col=0;
        string direction;
        cout<<"\nRozmieszczanie trzymasztowca"<<endl;
        print_map(playermap);
        while(1){
            cout<<"\nPodaj wpolrzedne poczatku statku (wiersz,kolumna), oraz gdzie ma byc skierowany (gora, dol, lewo, prawo)"<<endl;
            cin>>row;
            cin>>col;
            cin>>direction;
            if(playermap[row][col]==-1 && direction=="gora")
                if((((row-1)>=0 && playermap[row-1][col]==-1)&&((row-2)>=0 && playermap[row-2][col]==-1) && ((row-3)>=0 && playermap[row-3][col]==-1))
                        && check_up(row-3, col, playermap) && check_down(row, col, playermap)
                        && check_left(row , col, playermap) && check_left(row-1, col, playermap) && check_left(row-2, col, playermap) && check_left(row-3, col, playermap)
                        && check_right(row, col, playermap) && check_right(row-1, col, playermap) && check_right(row-2, col, playermap)){
                    setship(row, row-1, row-2, row-3, col, col , col, col, playermap);
                    break;
                }
            if(playermap[row][col]==-1 && direction=="dol")
                if((((row+1)<=9 && playermap[row+1][col]==-1)&&((row+2)<=9 && playermap[row+2][col]==-1))
                        && check_up(row, col, playermap) && check_down(row+2, col, playermap)
                        && check_left(row , col, playermap) && check_left(row+1, col, playermap) && check_left(row+2, col, playermap)
                        && check_right(row, col, playermap) && check_right(row+1, col, playermap) && check_right(row+2, col, playermap)){
                    setship(row, row+1, row+2, int row+3, col, col , col, col, playermap);
                    break;
                }
            if(playermap[row][col]==-1 && direction=="lewo")
                if((((col-1)>=0 && playermap[row][col-1]==-1)&&((col-2)>=0 && playermap[row][col-2]==-1))
                        && check_left(row, col-2, playermap) && check_right(row, col, playermap)
                        && check_up(row, col, playermap) && check_up(row, col-1, playermap) && check_up(row, col-2, playermap)
                        && check_down(row, col, playermap) && check_down(row, col-1, playermap) && check_down(row, col-2, playermap)){
                    setship(row, row, row, row, col, col-1, col-2, col-3, playermap);
                    break;
                }
            if(playermap[row][col]==-1 && direction=="prawo")
                if(((col+1)<=9 && playermap[row][col+1]==-1)&&((col+2)<=9 && playermap[row][col+2]==-1)
                        && check_left(row, col, playermap) && check_right(row, col+2, playermap)
                        && check_up(row, col, playermap) && check_up(row, col+1, playermap) && check_up(row, col+2, playermap)
                        && check_down(row, col, playermap) && check_down(row, col+1, playermap) && check_down(row, col+2, playermap)){
                    setship(row, row, row, rowm col, col+1, col+2, col+3, playermap);
                    break;
                }
            cout<<"Na ktoryms z pol juz znajduje sie statek, zakres wykracza poza mape lub na sasiednich polach jest juz statek"<<endl;
            }
        }
};




/*void place_ship(int playermap[][10], ship2 & ship){
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
            if((((row-1)>=0 && playermap[row-1][col]==-1)&&((row-2)>=0 && playermap[row-2][col]==-1))
                    && check_up(row-2, col, playermap) && check_down(row, col, playermap)
                    && check_left(row , col, playermap) && check_left(row-1, col, playermap) && check_left(row-2, col, playermap)
                    && check_right(row, col, playermap) && check_right(row-1, col, playermap) && check_right(row-2, col, playermap)){
                ship.setship(row, row-1, row-2, col, col , col, playermap);
                break;
            }
        if(playermap[row][col]==-1 && direction=="dol")
            if((((row+1)<=9 && playermap[row+1][col]==-1)&&((row+2)<=9 && playermap[row+2][col]==-1))
                    && check_up(row, col, playermap) && check_down(row+2, col, playermap)
                    && check_left(row , col, playermap) && check_left(row+1, col, playermap) && check_left(row+2, col, playermap)
                    && check_right(row, col, playermap) && check_right(row+1, col, playermap) && check_right(row+2, col, playermap)){
                ship.setship(row, row+1, row+2, col, col , col, playermap);
                break;
            }
        if(playermap[row][col]==-1 && direction=="lewo")
            if((((col-1)>=0 && playermap[row][col-1]==-1)&&((col-2)>=0 && playermap[row][col-2]==-1))
                    && check_left(row, col-2, playermap) && check_right(row, col, playermap)
                    && check_up(row, col, playermap) && check_up(row, col-1, playermap) && check_up(row, col-2, playermap)
                    && check_down(row, col, playermap) && check_down(row, col-1, playermap) && check_down(row, col-2, playermap)){
                ship.setship(row, row, row, col, col-1, col-2, playermap);
                break;
            }
        if(playermap[row][col]==-1 && direction=="prawo")
            if(((col+1)<=9 && playermap[row][col+1]==-1)&&((col+2)<=9 && playermap[row][col+2]==-1)
                    && check_left(row, col, playermap) && check_right(row, col+2, playermap)
                    && check_up(row, col, playermap) && check_up(row, col+1, playermap) && check_up(row, col+2, playermap)
                    && check_down(row, col, playermap) && check_down(row, col+1, playermap) && check_down(row, col+2, playermap)){
                ship.setship(row, row, row, col, col+1, col+2, playermap);
                break;
            }
        cout<<"Na ktoryms z pol juz znajduje sie statek lub zakres wykracza poza mape"<<endl;
    }

}*/

int main(){
    int playermap[10][10];
    int enemymap[10][10];
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            playermap[i][j]=-1;
            enemymap[i][j]=-1;
        }
    }
    ship2 player_ship21;
    ship2 player_ship22;
    ship2 player_ship23;
    ship2 player_ship24;
    ship3 player_ship31;
    ship3 player_ship32;
    ship3 player_ship33;
    cout<<"Nastepuje rozmieszczenie czterech dwumasztowcow"<<endl;
    player_ship21.placeship(playermap);
    player_ship22.placeship(playermap);
    player_ship23.placeship(playermap);
    player_ship24.placeship(playermap);
    cout<<"Nastepuje rozmieszczenie trzech trzymasztowcow"<<endl;
    player_ship31.placeship(playermap);
    player_ship32.placeship(playermap);
    player_ship33.placeship(playermap);
    print_map(playermap);
    return 0;
}
