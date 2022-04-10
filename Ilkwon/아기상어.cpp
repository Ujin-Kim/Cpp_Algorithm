#include<iostream>
#include <queue>
#include <memory.h>
using namespace std;
#define MAX 21

struct Shark{
    int y,x,sz,cnt;
};


int N,M;
int map[MAX][MAX]={};
Shark shark;
int visited[MAX][MAX]={};
int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
int ans = 0;

int isInside(int y, int x){
    if(y<1 || y>N || x<1 || x>N) return 0;
    return 1;
}

int bfs(){
    memset(visited,0,sizeof(visited));
    queue<Shark> que;

    que.push({shark.y,shark.x,shark.sz,shark.cnt});
    visited[shark.y][shark.x] = 1;
    
    while(!que.empty()){
        int y = que.front().y;
        int x = que.front().x;
        int sz = que.front().sz;
        int cnt = que.front().cnt;
        que.pop();

        for(int i=0;i<4; i++){
            int ny = y + dir[i][0];
            int nx = x + dir[i][1];

            if(!isInside(ny,nx) || visited[ny][nx] != 0 || map[ny][nx] > sz) continue;

            if(map[ny][nx] <= sz){
                visited[ny][nx] = visited[y][x] + 1;
                que.push({ny,nx,sz,cnt});
            }
        }
    }

    int min_dist = 9999999;
    int f_y = -1;
    int f_x = -1;
    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            if(min_dist > visited[y][x] && map[y][x] < shark.sz && map[y][x] != 0 && map[y][x] != 9 && visited[y][x] != 0){
                min_dist = visited[y][x];
                f_y = y;
                f_x = x;
            }
        }
    }
    
    if(f_y == -1){
        return 0;
    }

    map[f_y][f_x] = 9;
    map[shark.y][shark.x]= 0;

    shark.y = f_y;
    shark.x= f_x;
    shark.cnt++;

    if(shark.cnt == shark.sz){
        shark.sz++;
        shark.cnt=0;
    }
   
    return min_dist - 1;
}

int main(){

    cin>>N;

    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            cin>>map[y][x];
            if(map[y][x] ==9){
                shark.y = y;
                shark.x = x;
                shark.sz = 2;
                shark.cnt = 0;
            }
        }
    }

    int ans = 0;
    while(1){
        int flag = bfs();
        if(!flag) break;
        ans+=flag;
    }

    cout<<ans<<"\n";

    return 0;
}