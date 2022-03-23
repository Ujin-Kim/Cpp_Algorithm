#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
using namespace std;
#define MAX 21
#define INF 99999999
int N,M,F;

struct Taxi{
    int y,x;
    int fuel;
};

struct Node{
    int y,x,n,cnt;
};
int map[MAX][MAX]={};
vector<int> des[MAX][MAX]={};
int visited[MAX][MAX]={};
int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
int minDist = INF;
int p_y = -1;
int p_x = -1;
int p_n = -1;

int isInside(int y, int x){
    if(y<1 || y>N || x<1 || x>N) return 0;
    return 1;
}

Taxi taxi;

void check_dist(int y, int x, int n){

    memset(visited,0,sizeof(visited));
    queue<Node> que;
    que.push({y,x,n,0});
    visited[y][x]=1;
    int cnt = 0;
    int s_y = y;
    int s_x = x;

    while(!que.empty()){
        y = que.front().y;
        x = que.front().x;
        n = que.front().n;
        cnt = que.front().cnt;
        que.pop();

        if(y == taxi.y && x == taxi.x) break;

        for(int i=0;i<4;i++){
            int ny = y + dir[i][0];
            int nx = x + dir[i][1];

            if(!isInside(ny,nx) || visited[ny][nx] || map[ny][nx] == 1) continue;

            if(map[ny][nx] != 1){
                que.push({ny,nx,n,cnt+1});
                visited[ny][nx] = 1;
            }
        }

    }

    if(y == taxi.y && x == taxi.x && minDist > cnt){
        minDist = cnt;
        p_y = s_y;
        p_x = s_x;
        p_n = n;
    }
    

}

int go_des(int y, int x, int n){
    int d_y = -1;
    int d_x = -1;
    memset(visited,0,sizeof(visited));

    for(int y=1; y<=N;y++){
        for(int x=1; x<=N; x++){
            int sz = des[y][x].size();
            for(int i=0;i<sz;i++){
                if(des[y][x][i] == n){
                    d_y = y;
                    d_x = x;
                    break;
                }
            }
        }
        if(d_y != -1 && d_x != -1) break;
    }

    int d_cnt = 0;

    p_y = d_y;
    p_x = d_x;

    queue<Node> que;
    que.push({y,x,n,0});
    visited[y][x] = 1;

    while(!que.empty()){
        y = que.front().y;
        x = que.front().x;
        d_cnt = que.front().cnt;
        que.pop();

        if(d_cnt > taxi.fuel){
            d_cnt = -1;
            break;
        }

        if(y == d_y && x == d_x) break;

        for(int i=0;i<4;i++){
            int ny = y + dir[i][0];
            int nx = x + dir[i][1];

            if(!isInside(ny,nx) || visited[ny][nx] || map[ny][nx] == 1) continue;

            if(map[ny][nx] != 1){
                visited[ny][nx] = 1;
                que.push({ny,nx,n,d_cnt + 1});
            }
        }

    }
    if(y != d_y && x != d_x){
        d_cnt = -1;
    }
    return d_cnt;
}

void solve(){

    int chk = -1;
    for(int person = 1; person <= M; person++){
        
        for(int y=1; y<=N; y++){
            for(int x=1; x<=N; x++){
                if(map[y][x] > 1){
                    check_dist(y,x,map[y][x]);
                }
            }
        }

        if(minDist == INF){
            cout<<-1<<"\n";
            return;
        }
        taxi.y = p_y;
        taxi.x = p_x;
        taxi.fuel -= minDist;
        
        map[p_y][p_x] = 0;

        chk = go_des(p_y,p_x,p_n);

        if(chk == -1){
            cout<<-1<<"\n";
            return;
        }

        taxi.y = p_y;
        taxi.x = p_x;
        taxi.fuel -= chk;
        taxi.fuel += (chk * 2);

        p_y = -1;
        p_x = -1;
        minDist = INF;
        p_n = -1;
    }

    cout<<taxi.fuel<<"\n";
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >>F;

    for(int y=1; y<=N; y++){
        for(int x=1;x<=N;x++){
            cin>>map[y][x];
        }
    }

    int y,x;
    cin>>y>>x;

    taxi.y=y;
    taxi.x=x;
    taxi.fuel=F;

    for(int i=1;i<=M;i++){
        int s_y, s_x, d_y, d_x;
        cin>>s_y>>s_x>>d_y>>d_x;

        map[s_y][s_x] = i+1;
        des[d_y][d_x].push_back(i+1);
    }

    solve();

    return 0;
}