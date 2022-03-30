#include <iostream>
#include <queue>
#include <memory.h>
using namespace std;

int dir[8][2] = {{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};
int isInside(int y, int x){
    if(y<0 || y>=4 || x<0 || x>=4) return 0;
    return 1;
}
struct Fish{
    int y, x, d, live;
};

int map[4][4];
Fish fish[17] = {};
int ans = -99999999;

void solve(int s_y, int s_x, int s_d,int b_map[4][4], Fish b_fish[17], int score){
    int temp[4][4] = {};
    Fish f_temp[17] = {};
    
    for(int i=0;i<4; i++){
        for(int j=0; j<4; j++){
            temp[i][j] = b_map[i][j];
        }
    }

    for(int i=1;i<=16;i++){
        f_temp[i] = b_fish[i];
    }

    score += temp[s_y][s_x];
    s_d = f_temp[temp[s_y][s_x]].d;
    f_temp[temp[s_y][s_x]].live = 0;
    temp[s_y][s_x] = 0; 

    if(ans < score) ans = score;

    for(int i=1; i<=16; i++){
        int y = f_temp[i].y;
        int x = f_temp[i].x;
        int d = f_temp[i].d;
        int live = f_temp[i].live;

        if(live == 0) continue;

        int ny = y + dir[d][0];
        int nx = x + dir[d][1];

        while((ny == s_y && nx == s_x ) || !isInside(ny,nx)){
            d++;
            if(d == 8) d = 0;

            ny = y + dir[d][0];
            nx = x + dir[d][1];
        }
        if(temp[ny][nx] != 0){
            f_temp[i].y = ny;
            f_temp[i].x = nx;
            f_temp[i].d = d;

            f_temp[temp[ny][nx]].y = y;
            f_temp[temp[ny][nx]].x = x;

            temp[y][x] = temp[ny][nx];
            temp[ny][nx] = i;
        }
        else{
            f_temp[i].y = ny;
            f_temp[i].x = nx;
            f_temp[i].d = d;

            temp[y][x] = 0;
            temp[ny][nx] = i;
        }
    }

    int n_sy = s_y;
    int n_sx = s_x;    
    for(int i=0;i<3;i++){

        n_sy += dir[s_d][0];
        n_sx += dir[s_d][1];

        if(!isInside(n_sy,n_sx)) break;

        if(temp[n_sy][n_sx] != 0){
            solve(n_sy,n_sx,s_d,temp,f_temp,score);
        }
    }
     

}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            int n,d;
            cin>>n>>d;
            map[i][j] = n;
            fish[n].y = i;
            fish[n].x = j;
            fish[n].d = d-1;
            fish[n].live = 1;
        }
    }

    solve(0,0,0,map,fish,0);

    cout<<ans<<"\n";

    return 0;
}