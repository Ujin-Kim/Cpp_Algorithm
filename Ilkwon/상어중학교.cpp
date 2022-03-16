#include <iostream>
#include <memory.h>
#include <queue>
using namespace std;
#define MAX 21

int N,M;
int map[MAX][MAX] = {};
int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

struct Block{
    int y,x;
    int b_sz = 0;
    int r_cnt = 0;
    int map[MAX][MAX]={};
};
Block block_info;
int visited[MAX][MAX] = {};

int isInside(int y ,int x){
    if(y < 0 || y >= N || x < 0 || x >= N) return 0;
    return 1;
}

struct Node{
    int y,x,color;
};

void gravity(){

    for(int x=0; x<N; x++){
        for(int y=N - 1; y>0; y--){
            if(map[y][x]==-2){
                for(int k = y-1; k>=0; k--){
                    if(map[k][x] == -1) break;
                    if(map[k][x] != -2){
                        map[y][x] = map[k][x];
                        map[k][x] = -2;
                        break;
                    }
                }
            }
        }
    }

}

void rotate_90() {
	int temp[MAX][MAX] = {};

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			temp[N - x - 1][y] = map[y][x];
		}
	}
	memcpy(map, temp, sizeof(temp));
}
void bfs(int y, int x){
    queue<Node> que;
    que.push({y,x,map[y][x]});
    visited[y][x] = 1;
    int boom[MAX][MAX]={};
    int b_sz = 1;
    int r_cnt = 0;
    int s_y = y;
    int s_x = x;
    boom[y][x] = 1;
    while(!que.empty()){
        y = que.front().y;
        x = que.front().x;
        int color = que.front().color;
        que.pop();

        for(int i=0;i<4;i++){
            int ny = y + dir[i][0];
            int nx = x + dir[i][1];

            if(!isInside(ny,nx) || visited[ny][nx] || map[ny][nx] == -1 || map[ny][nx] == -2) continue;

            if(map[ny][nx] == color || map[ny][nx] == 0){
                if(map[ny][nx] == 0 ) r_cnt++;
                 visited[ny][nx] = 1;
                 b_sz++;
                 boom[ny][nx] = 1;
                 que.push({ny,nx,color});
            }
        }
    }

    if(block_info.b_sz < b_sz){
        block_info.b_sz = b_sz;
        block_info.y = s_y;
        block_info.x = s_x;
        memcpy(block_info.map,boom,sizeof(boom));
        block_info.r_cnt = r_cnt;
    }
    else if(block_info.b_sz == b_sz){
        if(block_info.r_cnt < r_cnt){
            block_info.r_cnt = r_cnt;
            block_info.y = s_y;
            block_info.x = s_x;
            memcpy(block_info.map,boom,sizeof(boom));
        }
        else if(block_info.r_cnt == r_cnt){
            if(block_info.y < s_y ){
                block_info.y = s_y;
                block_info.x = s_x;
                memcpy(block_info.map,boom,sizeof( boom));
            }
            else if(block_info.y == s_y){
                if(block_info.x < s_x){
                    block_info.y = s_y;
                    block_info.x = s_x;
                    memcpy(block_info.map,boom,sizeof(boom));
                }
            }
        }
    }

    for(int y = 0; y< N; y++){
        for(int x = 0; x<N; x++){
            if(map[y][x] == 0){
                visited[y][x] = 0;
            }
        }
    }

}

void solve(){
    
    int ans = 0;

    while(1){
        memset(visited,0,sizeof(visited));
        block_info.b_sz = 0;

        for(int y = 0; y < N; y++){
            for(int x = 0; x < N; x++){
                if(map[y][x] > 0 && visited[y][x] == 0){
                    bfs(y,x);
                }
            }
        }

        if(block_info.b_sz <= 1) break;

        //블록 폭파
        for(int y = 0; y < N; y++){
            for(int x = 0; x < N; x++){
                if(block_info.map[y][x] == 1){
                    map[y][x] = -2;
                }
            }
        }

        gravity();
        rotate_90();
        gravity();

        ans += (block_info.b_sz * block_info.b_sz);

    }

    cout<<ans<<endl;

}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin>>N>>M;

    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            cin>>map[y][x];
        }
    }
 
    solve();


    return 0;
}