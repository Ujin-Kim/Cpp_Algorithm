#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
using namespace std;
#define MAX 51

int R,C,T;
int map[MAX][MAX]={};
int dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int up_y = -1;
int dw_y = -1;

int isInside(int y, int x){
    if(y<1||y>R||x<1||x>C) return 0;
    return 1;
}

void spread() {
	queue<pair<pair<int, int>,int>> que;

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (map[i][j] != -1 && map[i][j] != 0) {
				que.push({{ i,j },map[i][j]});
			}
		}
	}

	while (!que.empty()) {
		int y = que.front().first.first;
		int x = que.front().first.second;
		int dust = que.front().second;
		int cnt = 0;
		que.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + dir[i][0];
			int nx = x + dir[i][1];

			if (map[ny][nx] != -1 && isInside(ny, nx)) {
				map[ny][nx] += (dust / 5);
				cnt++;
			}
		}
		map[y][x] = map[y][x] - (cnt*(dust / 5));
	}
}
void operate_air(){
    //up_air
    if(map[up_y - 1][1] != 0) map[up_y-1][1] = 0;

    for(int y=up_y-1; y>1; y--){
        map[y][1] = map[y -1][1];
        map[y-1][1] =0;
    }

    for(int x=1; x<C; x++){
        map[1][x] = map[1][x+1];
        map[1][x+1]=0;
    }

    for(int y=1; y<up_y; y++){
        map[y][C] = map[y + 1][C];
        map[y + 1][C] = 0;
    }

    for(int x=C; x>2; x--){
        map[up_y][x] = map[up_y][x-1];
        map[up_y][x-1] = 0;
    }

    //down_air
    if(map[dw_y+1][1] != 0) map[dw_y+1][1] =0;

    for(int y=dw_y+1; y<R;y++){
        map[y][1] = map[y+1][1];
        map[y+1][1] = 0;
    }

    for(int x=1; x<C; x++){
        map[R][x] = map[R][x+1];
        map[R][x+1] = 0;
    }

    for(int y=R; y>dw_y; y--){
        map[y][C] = map[y-1][C];
        map[y-1][C] = 0;
    }

    for(int x=C; x>2; x--){
        map[dw_y][x] = map[dw_y][x -1];
        map[dw_y][x-1] = 0;
    }
   
}

int main(){

    cin>>R>>C>>T;

    for(int y=1; y<=R; y++){
        for(int x=1; x<=C; x++){
            cin>>map[y][x];
            if(map[y][x] == -1){
                if(up_y == -1) up_y =  y;
                else dw_y = y;
            }
        }
    }
   
   while(T--){
       spread();
       operate_air();
   }

    int ans = 0;
   for(int y=1; y<=R; y++){
       for(int x=1; x<=C; x++){
           if(map[y][x] == -1) continue;
           ans+=map[y][x];
       }
   }

   cout<<ans<<"\n";

    return 0;
}