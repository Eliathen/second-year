#ifndef ENEMYCLASS_H_INCLUDED
#define ENEMYCLASS_H_INCLUDED

class enemy{
public:

    int hitrow, hitcol;
    bool hit;
    int fields;
    bool left, right, up, down;
    bool checked_l, checked_r, checked_u, checked_d;
    void sethit(){
        hit=false;
        left=right=up=down=false;
        checked_l=checked_r=checked_u=checked_d=false;
    }

    void place_ship_on_map(ship* enemymap[][10], ship* ship, int length){
        ship->setowner("enemy");
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
                done=ship->placeship(enemymap, row, col, direction, length, ship);
            }
        }

    void shoot(ship* playermap[][10]){
        if(hit==true){
            if(hitrow-1>=0 && checked_u==false){
                shoot_up(playermap);
                checked_u=true;
                return;
            }
            if(up==true){
                shoot_up(playermap);
                checked_d=checked_l=checked_r=true;
                return;
            }
            if(hitrow+1<=9 && checked_d==false){
                shoot_down(playermap);
                checked_d=true;
                return;
            }
            if(down==true){
                shoot_down(playermap);
                checked_u=checked_l=checked_r=true;
                return;
            }
            if(hitcol-1>=0 && checked_l==false){
                shoot_left(playermap);
                checked_l=true;
                return;
            }
            if(left==true){
                shoot_left(playermap);
                checked_d=checked_u=checked_r=true;
                return;
            }
            if(hitcol+1<=9 && checked_r==false){
                shoot_right(playermap);
                checked_r=true;
                return;
            }
            if(right==true){
                shoot_right(playermap);
                checked_d=checked_l=checked_u=true;
                return;
            }
            hit=false;
            checked_d=checked_l=checked_r=checked_u=false;
            up=down=left=right=false;


        }
        if(hit==false)
            no_prev_hit(playermap);
        }

    void no_prev_hit(ship* playermap[][10]){
        hitrow=rand()%10;
        hitcol=rand()%10;
        while((int)playermap[hitrow][hitcol]==0){
            hitrow=rand()%10;
            hitcol=rand()%10;
        }
        if((int)playermap[hitrow][hitcol]!=-2 && (int)playermap[hitrow][hitcol]!=-1 && (int)playermap[hitrow][hitcol]!=0){
            playermap[hitrow][hitcol]->get_damage();
            playermap[hitrow][hitcol]=(ship *)-2;
            hit=true;
            }
        else playermap[hitrow][hitcol]=(ship *)0;
    }

    void shoot_up(ship* playermap[][10]){
        if((hitrow-1)>=0 && (int)playermap[hitrow-1][hitcol]!=0 && (int)playermap[hitrow-1][hitcol]!=-1 && (int)playermap[hitrow-1][hitcol]!=-2){
            playermap[hitrow-1][hitcol]->get_damage();
            playermap[hitrow-1][hitcol]=(ship *)-2;
            hitrow-=1;
            up=true;
            }
        else {
            if((hitrow-1)>=0)
                playermap[hitrow-1][hitcol]=(ship *)0;
            up=false;
            }
        }

    void shoot_down(ship* playermap[][10]){
        if((hitrow+1)>=0 && (int)playermap[hitrow+1][hitcol]!=0 && (int)playermap[hitrow+1][hitcol]!=-1 && (int)playermap[hitrow+1][hitcol]!=-2){
            playermap[hitrow+1][hitcol]->get_damage();
            playermap[hitrow+1][hitcol]=(ship *)-2;
            hitrow+=1;
            down=true;
            }
        else {
            if((hitrow+1)<=9)
                playermap[hitrow+1][hitcol]=(ship *)0;
            down=false;
            }
        }

    void shoot_left(ship* playermap[][10]){
        if((hitcol-1)>=0 && (int)playermap[hitrow][hitcol-1]!=0 && (int)playermap[hitrow][hitcol-1]!=-1 && (int)playermap[hitrow][hitcol-1]!=-2){
            playermap[hitrow][hitcol-1]->get_damage();
            playermap[hitrow][hitcol-1]=(ship *)-2;
            hitcol-=1;
            left=true;
            }
        else {
            if((hitcol-1)>=0)
                playermap[hitrow][hitcol-1]=(ship *)0;
            left=false;
            }
        }

    void shoot_right(ship* playermap[][10]){
        if((hitcol+1)>=0 && (int)playermap[hitrow][hitcol+1]!=0 && (int)playermap[hitrow][hitcol+1]!=-1 && (int)playermap[hitrow][hitcol+1]!=-2){
            playermap[hitrow][hitcol+1]->get_damage();
            playermap[hitrow][hitcol+1]=(ship *)-2;
            hitcol+=1;
            right=true;
            }
        else {
            if((hitcol+1)<=9)
                playermap[hitrow][hitcol+1]=(ship *)0;
            right=false;
            }
        }

    void count_fields(ship* gamemap[][10]){
        this->fields=0;
        for(int i=0;i<10;i++)
            for(int j=0;j<10;j++)
                if((int)gamemap[i][j]!=-2 && (int)gamemap[i][j]!=-1 && (int)gamemap[i][j]!=0) fields++;
        }
};


#endif // ENEMYCLASS_H_INCLUDED
