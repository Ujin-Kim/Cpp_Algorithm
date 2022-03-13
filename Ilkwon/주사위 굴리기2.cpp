#include <iostream>
#include <queue>
#include <memory.h>
using namespace std;
#define MAX 21

int N,M,K;
int map[MAX][MAX]={};

//  2
//4 1 3
//  5
//  6

int isInside(int y, int x){
    if(y < 1 || y > N || x < 1 || x > M) return 0;
    return 1;
}
int dir[4][2]={{0,1},{0,-1},{-1,0},{1,0}}; 
int ans = 0;
int dice[6]={6,5,3,4,2,1};//0 -> 밑면, 1 -> 앞면, 2 -> 오른쪽, 3-> 왼쪽, 4 -> 뒷면, 5 -> 윗면
int visited[MAX][MAX]={};

int change_back(int d){

    switch(d){
        case 0:
            return 1;
            break;
        case 1:
            return 0;
            break;
        case 2:
            return 3;
            break;
        case 3:
            return 2;
            break;
    }
}

int change_dir(int d, int c){
    if(c == 0){
        switch(d){
            case 0:
                return 3;
                break;
            case 1:
                return 2;
                break;
            case 2:
                return 0;
                break;
            case 3:
                return 1;
                break;
        }
    }
    else if(c == 1){
        switch(d){
            case 0:
                return 2;
                break;
            case 1:
                return 3;
                break;
            case 2:
                return 1;
                break;
            case 3:
                return 0;
                break;
        }
    }
}

struct Node{
    int y,x;
};

void input(){
    cin>>N>>M>>K;

    for(int y=1; y<=N; y++){
        for(int x = 1; x<=M; x++){
            cin>>map[y][x];
        }
    }
}

int bfs(int y, int x){
    queue<Node> que;
    int res = 0;
    que.push({y,x});

    memset(visited,0,sizeof(visited));
    visited[y][x] = 1;
    
    while(!que.empty()){
        y = que.front().y;
        x = que.front().x;
        int sc = map[y][x];
        res += sc;
        que.pop();

        for(int i=0;i<4;i++){
            int ny = y + dir[i][0];
            int nx = x + dir[i][1];

            if(!isInside(ny,nx) || visited[ny][nx] != 0 || sc != map[ny][nx]) continue;
            if(sc == map[ny][nx]){
                visited[ny][nx] = 1;
                que.push({ny,nx});
            }
        }
    }

    return res;
}

void move(){
    //가장 먼저 오른쪽으로 이동

    int y = 1;
    int x = 1;
    int temp[6];
    int d = 0;
    //d = 0 => 오른쪽, d = 1 => 왼쪽, d = 2 => 위쪽, d = 3 => 아래쪽
    for(int i=1;i<=K;i++){
        int ny = y + dir[d][0];
        int nx = x + dir[d][1];


        if(!isInside(ny,nx)){
            d = change_back(d);
            ny = y + dir[d][0];
            nx = x + dir[d][1];
        }

        if(d==0){
            //오른쪽 => 밑면, 왼쪽면 => 윗면, 밑면 => 왼쪽면, 윗면 => 오른쪽면
            //0 밑, 1 앞, 2 오른, 3 왼, 4 뒤, 5 윗
            memcpy(temp,dice,sizeof(dice));
            dice[0] = temp[2];
            dice[5] = temp[3];
            dice[3] = temp[0];
            dice[2] = temp[5];
        }
        else if(d==1){
            //오른쪽 => 윗면, 왼쪽면 => 밑면, 밑면 => 오른쪽, 윗면 => 왼쪽면
            memcpy(temp,dice,sizeof(dice));
            dice[5] = temp[2];
            dice[0] = temp[3];
            dice[2] = temp[0];
            dice[3] = temp[5];
        }

        else if(d==2){
            //뒷면 => 밑면, 윗면 => 뒷면, 밑면 => 앞면, 앞면 => 윗면
            memcpy(temp,dice,sizeof(dice));
            dice[0] = temp[4];
            dice[4] = temp[5];
            dice[1] = temp[0];
            dice[5] = temp[1];
        }

        else if(d==3){
            //뒷면 => 윗면, 윗면 => 앞면, 밑면 => 뒷면, 앞면 => 밑면
            memcpy(temp,dice,sizeof(dice));
            dice[5] = temp[4];
            dice[1] = temp[5];
            dice[4] = temp[0];
            dice[0] = temp[1];
        }

        ans += bfs(ny,nx);

        if(dice[0] > map[ny][nx]){
            d = change_dir(d,0);
        }
        else if(dice[0] < map[ny][nx]){
            d = change_dir(d,1);
        }
        y = ny;
        x = nx;
    }

}

void solve(){
    input();

    move();
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    cout << ans << endl;

    return 0;
}