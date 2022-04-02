#include <iostream>
#include <queue>
#include <vector>
#include <memory.h>
using namespace std;
#define MAX 51

int N,M;
int map[MAX][MAX]={};
int visited[MAX][MAX]={};

struct Node{
    int y,x;
};

vector<Node> virus;

int dir[4][2] = {{0,1},{0,-1},{-1,0},{1,0}};

int isInside(int y, int x){
    if(y<1 || y>N || x<1 || x>N) return 0;
    return 1;
}
int ans = 99999999;
int used[MAX][MAX] = {};
void bfs(){

    queue<Node> que;
    memset(visited,0,sizeof(visited));
    int temp[MAX][MAX] = {};

    memcpy(temp,map,sizeof(map));
    
    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            if(temp[y][x] == 1){
                que.push({y,x});
                visited[y][x] = 1;
            }
        }
    }

    while(!que.empty()){
        int y = que.front().y;
        int x = que.front().x;
        int score = temp[y][x];
        que.pop();

        for(int i=0; i<4; i++){
            int ny = y + dir[i][0];
            int nx = x + dir[i][1];

            if(!isInside(ny,nx) || visited[ny][nx] ||  temp[ny][nx] == -1 ) continue;
            if(temp[ny][nx] == 0){
                visited[ny][nx] = 1;
                temp[ny][nx] = temp[y][x] + 1;
                que.push({ny,nx});
            }
            else if(temp[ny][nx] == -2){
                visited[ny][nx] = 1;
                temp[ny][nx] = score + 1;
                que.push({ny,nx});
            }
        }
    }

int max_ = -999999999;
int cnt = 0;
   for(int y=1; y<=N; y++){
       for(int x=1; x<=N; x++){
           if(temp[y][x] == 0) cnt++;
           if(max_ < temp[y][x] && map[y][x] != -2) max_ = temp[y][x];

       }
   }


   if(cnt > 0) return;
   if(ans > max_) ans = max_;

}

void dfs(int next, int br){
    if(br == M){

        bfs();

        return;
    }

    int sz = virus.size();

    for(int i=next; i<sz; i++){
        int y = virus[i].y;
        int x = virus[i].x;

        map[y][x] = 1;
        dfs(i+1, br + 1);
        map[y][x] = -2;
    }
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>N>>M;

    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            cin>>map[y][x];
            if(map[y][x] == 2){
                map[y][x] = -2;
                virus.push_back({y,x});
            }
            if(map[y][x] == 1){
                map[y][x] = -1;
            }
        }
    }

    dfs(0,0);

    if(ans == 99999999) 
        cout<<-1<<"\n";
    else
        cout<<ans - 1<<"\n";


    return 0;
}