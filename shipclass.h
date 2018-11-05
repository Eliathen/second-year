#ifndef SHIPCLASS_H_INCLUDED
#define SHIPCLASS_H_INCLUDED
class ship{
public:
    int row1, row2, row3, row4, col1, col2, col3, col4;
    int hit_points;
    int length;
    std::string owner;
    void setship(int row1, int row2, int col1, int col2, ship* gamemap[][10], ship* ship){
            this->hit_points=2;
            gamemap[row1][col1]=ship;
            gamemap[row2][col2]=ship;
    }
    void setship(int row1, int row2, int row3, int col1, int col2, int col3, ship* gamemap[][10], ship* ship){
            this->hit_points=3;
            gamemap[row1][col1]=ship;
            gamemap[row2][col2]=ship;
            gamemap[row3][col3]=ship;
    }
     void setship(int row1, int row2, int row3, int row4, int col1, int col2, int col3, int col4, ship* gamemap[][10], ship* ship){
            this->hit_points=4;
            gamemap[row1][col1]=ship;
            gamemap[row2][col2]=ship;
            gamemap[row3][col3]=ship;
            gamemap[row4][col4]=ship;
    }

    void setowner(std::string owner){
            this->owner=owner;
    }
    int check_up(int row, int col, ship* gamemap[][10]){
        if(row-1<0)
            return 1;
        else if((int)gamemap[row-1][col]==-1)
            return 1;
        else return 0;
    }

    int check_down(int row, int col, ship* gamemap[][10]){
        if(row+1>9)
            return 1;
        else if((int)gamemap[row+1][col]==-1)
            return 1;
        else return 0;
    }

    int check_left(int row, int col, ship* gamemap[][10]){
        if(col-1<0)
            return 1;
        else if((int)gamemap[row][col-1]==-1)
            return 1;
        else return 0;
    }

    int check_right(int row, int col, ship* gamemap[][10]){
        if(col+1>9)
            return 1;
        else if((int)gamemap[row][col+1]==-1)
            return 1;
        else return 0;
    }

    bool placeship(ship* gamemap[][10], int row, int col, std::string direction, int length, ship* ship){
        this->length=length;
        if(length==2){
            if((int)gamemap[row][col]==-1 && direction=="gora")
                if((((row-1)>=0 && (int)gamemap[row-1][col]==-1))
                        && check_up(row-1, col, gamemap) && check_down(row, col, gamemap)
                        && check_left(row , col, gamemap) && check_left(row-1, col, gamemap)
                        && check_right(row, col, gamemap) && check_right(row-1, col, gamemap)){
                    setship(row, row-1, col, col , gamemap, ship);
                    return true;
                }
            if((int)gamemap[row][col]==-1 && direction=="dol")
                if((((row+1)<=9 && (int)gamemap[row+1][col]==-1))
                        && check_up(row, col, gamemap) && check_down(row+1, col, gamemap)
                        && check_left(row , col, gamemap) && check_left(row+1, col, gamemap)
                        && check_right(row, col, gamemap) && check_right(row+1, col, gamemap)){
                    setship(row, row+1, col, col , gamemap, ship);
                    return true;
                }
            if((int)gamemap[row][col]==-1 && direction=="lewo")
                if((((col-1)>=0 && (int)gamemap[row][col-1]==-1))
                        && check_left(row, col-1, gamemap) && check_right(row, col, gamemap)
                        && check_up(row, col, gamemap) && check_up(row, col-1,gamemap)
                        && check_down(row, col, gamemap) && check_down(row, col-1, gamemap)){
                    setship(row, row, col, col-1, gamemap, ship);
                    return true;
                }
            if((int)gamemap[row][col]==-1 && direction=="prawo")
                if(((col+1)<=9 && (int)gamemap[row][col+1]==-1)
                        && check_left(row, col, gamemap) && check_right(row, col+1, gamemap)
                        && check_up(row, col, gamemap) && check_up(row, col+1, gamemap)
                        && check_down(row, col, gamemap) && check_down(row, col+1, gamemap)){
                    setship(row, row, col, col+1, gamemap, ship);
                    return true;
                    }
            return false;
            }
    if(length==3){
        if((int)gamemap[row][col]==-1 && direction=="gora")
            if((((row-1)>=0 && (int)gamemap[row-1][col]==-1)&&((row-2)>=0 && (int)gamemap[row-2][col]==-1))
                    && check_up(row-2, col, gamemap) && check_down(row, col, gamemap)
                    && check_left(row , col, gamemap) && check_left(row-1, col, gamemap) && check_left(row-2, col, gamemap)
                    && check_right(row, col, gamemap) && check_right(row-1, col, gamemap) && check_right(row-2, col, gamemap)){
                setship(row, row-1, row-2, col, col , col, gamemap, ship);
                return true;
            }
        if((int)gamemap[row][col]==-1 && direction=="dol")
            if((((row+1)<=9 && (int)gamemap[row+1][col]==-1)&&((row+2)<=9 && (int)gamemap[row+2][col]==-1))
                    && check_up(row, col, gamemap) && check_down(row+2, col, gamemap)
                    && check_left(row , col, gamemap) && check_left(row+1, col, gamemap) && check_left(row+2, col, gamemap)
                    && check_right(row, col, gamemap) && check_right(row+1, col, gamemap) && check_right(row+2, col, gamemap)){
                setship(row, row+1, row+2, col, col , col, gamemap, ship);
                return true;
            }
        if((int)gamemap[row][col]==-1 && direction=="lewo")
            if((((col-1)>=0 && (int)gamemap[row][col-1]==-1)&&((col-2)>=0 && (int)gamemap[row][col-2]==-1))
                    && check_left(row, col-2, gamemap) && check_right(row, col, gamemap)
                    && check_up(row, col, gamemap) && check_up(row, col-1, gamemap) && check_up(row, col-2, gamemap)
                    && check_down(row, col, gamemap) && check_down(row, col-1, gamemap) && check_down(row, col-2, gamemap)){
                setship(row, row, row, col, col-1, col-2, gamemap, ship);
                return true;
            }
        if((int)gamemap[row][col]==-1 && direction=="prawo")
            if(((col+1)<=9 && (int)gamemap[row][col+1]==-1)&&((col+2)<=9 && (int)gamemap[row][col+2]==-1)
                    && check_left(row, col, gamemap) && check_right(row, col+2, gamemap)
                    && check_up(row, col, gamemap) && check_up(row, col+1, gamemap) && check_up(row, col+2, gamemap)
                    && check_down(row, col, gamemap) && check_down(row, col+1, gamemap) && check_down(row, col+2, gamemap)){
                setship(row, row, row, col, col+1, col+2, gamemap, ship);
                return true;
               }
        return false;
        }
    if(length==4){
        if((int)gamemap[row][col]==-1 && direction=="gora")
            if((((row-1)>=0 && (int)gamemap[row-1][col]==-1)&&((row-3)>=0 && (int)gamemap[row-2][col]==-1) && ((row-3)>=0 && (int)gamemap[row-3][col]==-1))
                    && check_up(row-3, col, gamemap) && check_down(row, col, gamemap)
                    && check_left(row , col, gamemap) && check_left(row-1, col, gamemap) && check_left(row-2, col, gamemap) && check_left(row-3, col, gamemap)
                    && check_right(row, col, gamemap) && check_right(row-1, col, gamemap) && check_right(row-2, col, gamemap) && check_right(row-3, col, gamemap)){
                setship(row, row-1, row-2, row-3, col, col , col, col, gamemap, ship);
                return true;
            }
        if((int)gamemap[row][col]==-1 && direction=="dol")
            if((((row+1)<=9 && (int)gamemap[row+1][col]==-1)&&((row+2)<=9 && (int)gamemap[row+2][col]==-1) && ((row+3)>=0 && (int)gamemap[row+3][col]==-1))
                    && check_up(row, col, gamemap) && check_down(row+3, col, gamemap)
                    && check_left(row , col, gamemap) && check_left(row+1, col, gamemap) && check_left(row+2, col, gamemap) && check_left(row+3, col, gamemap)
                    && check_right(row, col, gamemap) && check_right(row+1, col, gamemap) && check_right(row+2, col, gamemap) && check_right(row+3, col, gamemap)){
                setship(row, row+1, row+2, row+3, col, col, col, col, gamemap, ship);
                return true;
            }
        if((int)gamemap[row][col]==-1 && direction=="lewo")
            if((((col-1)>=0 && (int)gamemap[row][col-1]==-1)&&((col-2)>=0 && (int)gamemap[row][col-2]==-1) && ((col-3)>=0 && (int)gamemap[row][col-3]==-1))
                    && check_left(row, col-3, gamemap) && check_right(row, col, gamemap)
                    && check_up(row, col, gamemap) && check_up(row, col-1, gamemap) && check_up(row, col-2, gamemap) && check_up(row, col-3, gamemap)
                    && check_down(row, col, gamemap) && check_down(row, col-1, gamemap) && check_down(row, col-2, gamemap) && check_down(row, col-3, gamemap)){
                setship(row, row, row, row, col, col-1, col-2, col-3, gamemap, ship);
                return true;
            }
        if((int)gamemap[row][col]==-1 && direction=="prawo")
            if(((col+1)<=9 && (int)gamemap[row][col+1]==-1)&&((col+2)<=9 && (int)gamemap[row][col+2]==-1 && ((col+3)>=0 && (int)gamemap[row][col+3]==-1))
                    && check_left(row, col, gamemap) && check_right(row, col+3, gamemap)
                    && check_up(row, col, gamemap) && check_up(row, col+1, gamemap) && check_up(row, col+2, gamemap) && check_up(row, col+3, gamemap)
                    && check_down(row, col, gamemap) && check_down(row, col+1, gamemap) && check_down(row, col+2, gamemap) && check_down(row, col+3, gamemap)){
                setship(row, row, row, row, col, col+1, col+2, col+3, gamemap, ship);
                return true;
            }
        return false;
        }
    return false;
    }

    int get_damage(){
        hit_points--;
        if(hit_points==0 && owner=="enemy") return 15;
        if(owner=="enemy") return 5;
        return 0;
    }

};


#endif // SHIPCLASS_H_INCLUDED
