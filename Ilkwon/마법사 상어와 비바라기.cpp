#include <iostream>
#include <queue>
#include <memory.h>
using namespace std;
#define MAX 51

int dir[8][2] = {{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1}};
int dia_dir[4][2] = {{-1,-1},{-1,1},{1,-1},{1,1}};

int N,M;
int map[MAX][MAX]={};
int visited[MAX][MAX] = {};

struct Dir{
    int d, s;
};

struct Node{
    int y,x;
};

queue<Dir> dque;
queue<Node> que;
int isInside(int y, int x){
    if(y < 1 || y > N || x < 1 || x > N) return 0;
    return 1;
}

pair<int,int> through_index(int y, int x, int d){
    
    pair<int,int> p;

    if(!isInside(y,x)){
        switch(d){
            case 0:
                p.first = y;
                p.second = N + x;
                break;
            case 1:
                p.first = y < 1 ? N + y : y;
                p.second = x < 1 ? N + x : x;
                break;
            case 2:
                p.first = N + y;
                p.second = x;
                break;
            case 3:
                p.first =  y < 1 ? y + N : y;
                p.second = x > N ? x - N : x;
                break;
            case 4:
                p.first = y;
                p.second = x - N;
                break;
            case 5:
                p.first = y > N ? y - N : y;
                p.second = x > N ? x - N : x;
                break;
            case 6:
                p.first = y - N;
                p.second = x;
                break;
            case 7:
                p.first = y > N ? y - N : y;
                p.second = x < 1 ? N + x : x;
                break;
            default:
                break;

        }
    }
    else{
        p.first = y;
        p.second = x;
    }
 return p;
}

//step1. 구름 움직이기
void c_move(int d, int s){

    queue<Node> c_que;
    memset(visited,0,sizeof(visited));
    
    while(!que.empty()){
        int y = que.front().y;
        int x = que.front().x;
        que.pop();

        int ny = y;
        int nx = x;
        for(int i=0;i<s;i++){
            ny += dir[d][0];
            nx += dir[d][1];

            pair<int,int> p = through_index(ny,nx,d);

            ny = p.first;
            nx = p.second;
        }

        map[ny][nx]++;
        visited[ny][nx] =1;

        c_que.push({ny,nx});
    }

    //물 복사 버그 시작

    while(!c_que.empty()){
        int y = c_que.front().y;
        int x = c_que.front().x;
        c_que.pop();

        int cnt = 0;
        for(int i =0; i<4; i++){
            int ny = y + dia_dir[i][0];
            int nx = x + dia_dir[i][1];

            if(!isInside(ny,nx)) continue;

            if(map[ny][nx] > 0) cnt++;
        }

        map[y][x] += cnt;
    }
}

void c_make(){
    for(int y = 1; y<=N; y++){
        for(int x = 1; x <= N; x++){
            if(!visited[y][x] && map[y][x] >=2){
                que.push({y,x});
                map[y][x]-=2;
            }
        }
    }
}

void solve(){

    int ans = 0;
    for(int i=0; i<M; i++){
        c_move(dque.front().d, dque.front().s);
        dque.pop();
        c_make();
    }

    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            ans+=map[y][x];
        }
    }

    cout<<ans<<endl;

}


int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin>>N>>M;

    for(int y = 1; y<=N; y++){
        for(int x = 1; x <= N; x++){
            cin>>map[y][x];
        }
    }

    que.push({N,1});
    que.push({N,2});
    que.push({N-1,1});
    que.push({N-1,2});

    for(int i=0;i<M;i++){
        int d,s;
        cin>>d>>s;
        dque.push({d - 1,s});
    }

    solve();

    return 0;
}