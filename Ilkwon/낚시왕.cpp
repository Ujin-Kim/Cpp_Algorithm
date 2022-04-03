#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <memory.h>
using namespace std;
#define MAX 101

int R,C,M;
int dir[5][2] = {{0,0},{-1,0},{1,0},{0,1},{0,-1}};
struct Shark{
    int s,d,z;
};

vector<Shark> shark[MAX][MAX];

bool comp(Shark front, Shark back){
    return front.z > back.z;
}

int ans = 0;

int catch_shark(int x){

    int score = 0;
   
    for(int y = 1; y<=R; y++){
        if(!shark[y][x].empty()){
            score = shark[y][x][0].z;
            shark[y][x].clear();
            break;
        }
    }

    return score;
}

void move_shark(){

    vector<Shark> shark2[MAX][MAX];

    for(int y=1; y<=R; y++){
        for(int x=1; x<=C; x++){
            if(shark[y][x].empty()) continue;
            int s = shark[y][x][0].s;
            int d = shark[y][x][0].d;
            int z = shark[y][x][0].z;

            if (d <= 2) 
                s %= (2 * R - 2);
            else 
                s %= (2 * C - 2);

            int ny = y;
            int nx = x;
            
            for(int i=0; i<s; i++){
                ny += dir[d][0];
                nx += dir[d][1];

                if(ny <1 || ny >R || nx <1 || nx > C){
                    ny -= dir[d][0];
                    nx -= dir[d][1];

                    if(d==1) d=2;
                    else if(d==2) d=1;
                    else if(d==3) d=4;
                    else if(d==4) d=3;

                    ny += dir[d][0];
                    nx += dir[d][1];
                }
            }

            shark2[ny][nx].push_back({s,d,z});
        }
    }

    for(int y=1; y<=R; y++){
        for(int x=1; x<=C; x++){
            shark[y][x] = shark2[y][x];
        }
    }
}

void kill_shark(){

    for(int y=1; y<=R; y++){
        for(int x=1; x<=C; x++){
            if(shark[y][x].size() <= 1) continue;

            sort(shark[y][x].begin(), shark[y][x].end(),comp);
            Shark temp = shark[y][x][0];

            shark[y][x].clear();

            shark[y][x].push_back(temp);
        }
    }
}

void solve(){

    for(int i=1; i<=C; i++){

        ans += catch_shark(i);
        move_shark();
        kill_shark();
    }

    cout<<ans<<"\n";
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>R>>C>>M;

    for(int i=0; i<M; i++){
        int r,c,s,d,z;
        cin>>r>>c>>s>>d>>z;
        shark[r][c].push_back({s,d,z});
    }

    solve();

    return 0;
}