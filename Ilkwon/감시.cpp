#include <iostream>
#include <vector>
#include <memory.h>
using namespace std;
#define MAX 9

int map[MAX][MAX]={};
int dir[4][2] ={{0,1},{1,0},{0,-1},{-1,0}};
int N,M;
struct CCTV{
    int y,x;
    int num;
};
vector<CCTV> cctv;
vector<int> angle;

int ans = 99999999;

int isInside(int y, int x){
    if( y<1 || y>N || x<1 || x>M) return 0;
    return 1;
}

void dfs(int br){

    if(br == cctv.size()){
        int temp[MAX][MAX];
        memcpy(temp,map,sizeof(map));


        for(int i=0; i<cctv.size(); i++){
            int y = cctv[i].y;
            int x = cctv[i].x;
            int num = cctv[i].num;

            int ny = y + dir[angle[i]][0];
            int nx = x + dir[angle[i]][1];

            switch(num){
                case 1:{
                    while(1){
                        if(!isInside(ny,nx) || temp[ny][nx] == 6) break;

                        if(temp[ny][nx] == 0)
                            temp[ny][nx] = -1;

                        ny += dir[angle[i]][0];
                        nx += dir[angle[i]][1];
                    }
                }
                    break;
                case 2:{
                    while(1){
                        if(!isInside(ny,nx) || temp[ny][nx] == 6) break;

                        if(temp[ny][nx] == 0)
                            temp[ny][nx] = -1;

                        ny += dir[angle[i]][0];
                        nx += dir[angle[i]][1];
                    }

                    int b_dir = 0;
                    if(angle[i] == 0) b_dir = 2;
                    if(angle[i] == 1) b_dir = 3;
                    if(angle[i] == 2) b_dir = 0;
                    if(angle[i] == 3) b_dir = 1;

                    ny = y+dir[b_dir][0];
                    nx = x+dir[b_dir][1];
                    while(1){
                        if(!isInside(ny,nx) || temp[ny][nx] == 6) break;

                        if(temp[ny][nx] == 0)
                            temp[ny][nx] = -1;

                        ny += dir[b_dir][0];
                        nx += dir[b_dir][1];
                    }
                }
                    break;

                case 3:{
                    while(1){
                        if(!isInside(ny,nx) || temp[ny][nx] == 6) break;

                        if(temp[ny][nx] == 0)
                            temp[ny][nx] = -1;

                        ny += dir[angle[i]][0];
                        nx += dir[angle[i]][1];
                    }
                    int d_dir = 0;
                    if(angle[i] == 0) d_dir = 1;
                    if(angle[i] == 1) d_dir = 2;
                    if(angle[i] == 2) d_dir = 3;
                    if(angle[i] == 3) d_dir = 0;

                    ny = y + dir[d_dir][0];
                    nx = x + dir[d_dir][1];

                    while(1){
                        if(!isInside(ny,nx) || temp[ny][nx] == 6) break;

                        if(temp[ny][nx] == 0)
                            temp[ny][nx] = -1;

                        ny += dir[d_dir][0];
                        nx += dir[d_dir][1];
                    }
                }

                    break;

                case 4:{
                    while(1){
                        if(!isInside(ny,nx) || temp[ny][nx] == 6) break;

                        if(temp[ny][nx] == 0)
                            temp[ny][nx] = -1;

                        ny += dir[angle[i]][0];
                        nx += dir[angle[i]][1];
                    }

                    int l_dir = 0;
                    int r_dir = 0;

                    if(angle[i] == 0){
                        l_dir = 3;
                        r_dir = 1;
                    }
                    if( angle[i] == 1){
                        l_dir = 0;
                        r_dir = 2;
                    }
                    if(angle[i] == 2){
                        l_dir = 3;
                        r_dir = 1;
                    }
                    if(angle[i] == 3){
                        l_dir = 2;
                        r_dir = 0;
                    }

                    ny = y + dir[l_dir][0];
                    nx = x + dir[l_dir][1];
                    while(1){
                        if(!isInside(ny,nx) || temp[ny][nx] == 6) break;

                        if(temp[ny][nx] == 0)
                            temp[ny][nx] = -1;

                        ny += dir[l_dir][0];
                        nx += dir[l_dir][1];
                    }

                    ny = y + dir[r_dir][0];
                    nx = x + dir[r_dir][1];
                    while(1){
                        if(!isInside(ny,nx) || temp[ny][nx] == 6) break;

                        if(temp[ny][nx] == 0)
                            temp[ny][nx] = -1;

                        ny += dir[r_dir][0];
                        nx += dir[r_dir][1];
                    }
                }
                    break;

                case 5:{
                    for(int j=0; j<4; j++){
                        ny = y + dir[j][0];
                        nx = x + dir[j][1];

                        if(!isInside(ny,nx) || temp[ny][nx] == 6) continue;

                        while(1){
                            if(!isInside(ny,nx) || temp[ny][nx] == 6) break;

                            if(temp[ny][nx] == 0)
                                temp[ny][nx] = -1;

                            ny += dir[j][0];
                            nx += dir[j][1]; 
                        }
                    }
                }
                    break;
                }

            }
            int cnt = 0;
            for(int y=1; y<=N; y++){
                for(int x=1; x<=M; x++){
                    if(temp[y][x] == 0) cnt++;
                }
            }
            if(ans > cnt) ans = cnt;
            return;
        }

    for(int i=0; i<4; i++){
        angle.push_back(i);
        dfs(br+1);
        angle.pop_back();
    }
}

int main(){

    cin>>N>>M;

    for(int y=1; y<=N; y++){
        for(int x=1; x<=M; x++){
            cin>>map[y][x];
            if(map[y][x] != 0 && map[y][x] !=6){
                cctv.push_back({y,x,map[y][x]});
            }
        }
    }

    dfs(0);

    cout<<ans<<"\n";

    return 0;
}