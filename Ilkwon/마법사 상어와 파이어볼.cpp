#include <iostream>
#include <memory.h>
#include <vector>
using namespace std;
#define MAX 51
struct Fire{
    int m,s,d,visit;
};

vector<Fire> fire_ball[MAX][MAX];

int N,M,K;
int dir[8][2]={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
int oddEven_dir[4] = {0,2,4,6};
int else_dir[4] = {1,3,5,7};
int lev = 0;

void move(){
    ++lev;
    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            if(fire_ball[y][x].empty()) continue;

            int sz = fire_ball[y][x].size();

            for(int i=0;i<sz;i++){
                int d= fire_ball[y][x][i].d;
                int m =fire_ball[y][x][i].m;
                int s = fire_ball[y][x][i].s;

                if(fire_ball[y][x][i].visit == 1) continue;

                int ny = y + dir[d][0] * (s%N);
                int nx = x + dir[d][1] * (s%N);

                if(ny < 1) ny += N;
                if(ny > N) ny -= N;
                if(nx < 1) nx += N;
                if(nx > N) nx -= N;

                fire_ball[ny][nx].push_back({m,s,d,1});
            }
            vector<Fire> temp;

            for(int i=0; i<fire_ball[y][x].size();i++){
                if(fire_ball[y][x][i].visit == 0) continue;
                temp.push_back({fire_ball[y][x][i].m,fire_ball[y][x][i].s,fire_ball[y][x][i].d,1});
            }
            fire_ball[y][x].clear();
            fire_ball[y][x] = temp;
            //cout<<fire_ball[y][x].size()<<endl;
        }
    }

    vector<Fire> temp;
    for(int y = 1; y<= N; y++){
        for(int x = 1; x<= N; x++){
            int sz = fire_ball[y][x].size();

            for(int i=0; i< sz; i++){
                int m = fire_ball[y][x][i].m;
                int s = fire_ball[y][x][i].s;
                int d = fire_ball[y][x][i].d;

                if(m == 0 ) continue;

                temp.push_back({m,s,d,0});
            }

            fire_ball[y][x].clear();
            fire_ball[y][x] = temp;
            temp.clear();
        }
    }
}

void fireBall(){
    vector<Fire> temp;

    for(int y = 1; y<=N; y++){
        for(int x = 1; x<=N; x++){
            int sz = fire_ball[y][x].size();
            if(sz == 0) continue;

            if(sz == 1){
                fire_ball[y][x][0].visit = 0;
                continue;
            } 

            int m = 0;
            int s = 0;
            int o_cnt = 0;
            int e_cnt = 0;
            for(int i=0; i< sz; i++){
                m+=fire_ball[y][x][i].m;
                s+=fire_ball[y][x][i].s;
                if(fire_ball[y][x][i].d %2 ==0) e_cnt++;
                else o_cnt++;
            }
            if(m/5 == 0){
                fire_ball[y][x].clear();
                continue;
            }
            
            for(int i=0;i<4;i++){
                if(o_cnt == 0 || e_cnt == 0){
                    temp.push_back({m/5,s/sz,oddEven_dir[i],0});
                }
                else{
                    temp.push_back({m/5,s/sz,else_dir[i],0});
                }
            }
            fire_ball[y][x] = temp;
            temp.clear();
        }
    }
}

void solve(){
    int ans = 0;

    for(int i=0;i<K;i++){

        move();
        fireBall();
    }

    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            int sz = fire_ball[y][x].size();

            if(sz==0) continue;

            for(int i=0;i<sz;i++){
                ans+=fire_ball[y][x][i].m;
            }
        }
    }

    printf("%d\n",ans);
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>N>>M>>K;

    for(int i=0;i<M;i++){
        int y,x,m,s,d;
        cin>>y>>x>>m>>s>>d;
        fire_ball[y][x].push_back({m,s,d,0});
    }

    solve();


    return 0;
}