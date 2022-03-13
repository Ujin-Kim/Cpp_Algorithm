#include <iostream>
#include <queue>
#include <vector>
#include <memory.h>
using namespace std;

#define MAX 21

int right_dir[3][2] = {{-1,1},{0,1},{1,1}};
int left_dir[3][2] = {{-1,-1},{0,-1},{1,-1}};
int up_dir[3][2] = {{-1,-1},{-1,0},{-1,1}};
int down_dir[3][2] = {{1,-1},{1,0},{1,1}};

int dir[4][2] = {{0,1},{0,-1},{-1,0},{1,0}};

int map[MAX][MAX] = {};
int heat[MAX][MAX] = {};
int wall[MAX][MAX][4] = {}; //동, 서, 북, 남
int R,C,K,W;
int visited[MAX][MAX]={};
int chk_cnt = 0;

struct Node{
    int y, x, d, c;
};

struct Temp{
  int y,x,tp;  
};

int isInside(int y, int x){
    if(y<1 || y>R || x<1 || x>C) return 0;
    return 1;
}

void bfs(int y, int x, int d){
    queue<Node> que;
    que.push({y,x,d,4});
    memset(visited,0,sizeof(visited));
    visited[y][x] = 1;

    while(!que.empty()){
        y = que.front().y;
        x = que.front().x;
        d = que.front().d;
        int c = que.front().c;
        que.pop();

        if(c==0) continue;

            for(int i=0;i<3;i++){
                if(d==1){
                int ny = y + right_dir[i][0];
                int nx = x + right_dir[i][1];

                if(!isInside(ny,nx) || visited[ny][nx]) continue;
                int chk = 0;
                switch(i){
                    case 0:
                        if(!wall[y][x][2] && !wall[ny][nx][1]){
                            map[ny][nx]+=c;
                            chk = 1;
                        }
                        break;
                    case 1:
                        if(!wall[y][x][0]){
                            map[ny][nx]+=c;
                            chk = 1;
                        }
                        break;
                    case 2:
                        if(!wall[y][x][3] && !wall[ny][nx][1]){
                            map[ny][nx] += c;
                            chk = 1;
                        }
                        break;
                }
                if(chk){
                    visited[ny][nx] = 1;
                    que.push({ny,nx,d,c-1});
                }
            }
            else if(d==2){
                int ny = y + left_dir[i][0];
                int nx = x + left_dir[i][1];

                if(!isInside(ny,nx) || visited[ny][nx]) continue;
                int chk = 0;
                switch(i){
                    case 0:
                        if(!wall[y][x][2] && !wall[ny][nx][0]){
                            map[ny][nx]+=c;
                            chk = 1;
                        }
                        break;
                    case 1:
                        if(!wall[y][x][1]){
                            map[ny][nx]+=c;
                            chk = 1;
                        }
                        break;
                    case 2:
                        if(!wall[y][x][3] && !wall[ny][nx][0]){
                            map[ny][nx] += c;
                            chk = 1;
                        }
                        break;
                }
                if(chk){
                    visited[ny][nx] = 1;
                    que.push({ny,nx,d,c-1});
                }
            }
            else if(d==3){
                int ny = y + up_dir[i][0];
                int nx = x + up_dir[i][1];

                if(!isInside(ny,nx) || visited[ny][nx]) continue;
                int chk = 0;
                switch(i){
                    case 0:
                        if(!wall[y][x][1] && !wall[ny][nx][3]){
                            map[ny][nx]+=c;
                            chk = 1;
                        }
                        break;
                    case 1:
                        if(!wall[y][x][2]){
                            map[ny][nx]+=c;
                            chk = 1;
                        }
                        break;
                    case 2:
                        if(!wall[y][x][0] && !wall[ny][nx][3]){
                            map[ny][nx] += c;
                            chk = 1;
                        }
                        break;
                }
                if(chk){
                    visited[ny][nx] = 1;
                    que.push({ny,nx,d,c-1});
                }
            }
            else if(d==4){
                int ny = y + down_dir[i][0];
                int nx = x + down_dir[i][1];

                if(!isInside(ny,nx) || visited[ny][nx]) continue;
                int chk = 0;
                switch(i){
                    case 0:
                        if(!wall[ny][nx][2] && !wall[y][x][1]){
                            map[ny][nx]+=c;
                            chk = 1;
                        }
                        break;
                    case 1:
                        if(!wall[y][x][3]){
                            map[ny][nx]+=c;
                            chk = 1;
                        }
                        break;
                    case 2:
                        if(!wall[ny][nx][2] && !wall[y][x][0]){
                            map[ny][nx] += c;
                            chk = 1;
                        }
                        break;
                }
                if(chk){
                    visited[ny][nx] = 1;
                    que.push({ny,nx,d,c-1});
                }
            }
        }
    }
  //  for(int y=1;y<=R;y++){
    //    for(int x=1;x<=C;x++){
    //        cout<<map[y][x]<<" ";
    //    }
    //    cout<<endl;
  //  }
   // cout<<endl;

}

//step1. 열 퍼뜨리기
void spread_heat(){

    for(int i=1;i<=R;i++){
        for(int j=1;j<=C;j++){
            if(heat[i][j] != 0 && heat[i][j] != 5){
                if(heat[i][j] == 1){
                    map[i][j+1] += 5;
                    bfs(i, j+1, heat[i][j]);
                }
                else if(heat[i][j] == 2){
                    map[i][j-1] += 5;
                    bfs(i,j-1,heat[i][j]);
                }
                else if(heat[i][j] == 3){
                    map[i - 1][j] += 5;
                    bfs(i-1,j,heat[i][j]);
                }
                else if(heat[i][j] == 4){
                    map[i + 1][j] += 5;
                    bfs(i+1,j,heat[i][j]);
                }
            }
        }
    }

}

//step2. 열 조정하기
void adjust_temp(){
    queue<Temp> que;
    
    int h_temp[MAX][MAX]={};
    memcpy(h_temp,map,sizeof(map));


    for(int y=1;y<=R;y++){
        for(int x=1;x<=C;x++){
            if(map[y][x] != 0){
                que.push({y,x,map[y][x]});
            }
        }
    }

    while(!que.empty()){
        int y = que.front().y;
        int x = que.front().x;
        int tp = que.front().tp;
        que.pop();

        for(int i=0;i<4;i++){
            int ny = y + dir[i][0];
            int nx = x + dir[i][1];

            if(!isInside(ny,nx) || wall[y][x][i] == 1) continue;

            int dif = (tp - h_temp[ny][nx]) /4;

            if(tp > h_temp[ny][nx]){
                map[y][x] -= dif;
                map[ny][nx] += dif;
            }

        }

    }

}

//step3. 바깥 외각 온도 1씩 감소

void sub_outline(){

    for(int i=1;i<=C;i++){
        if(map[1][i] > 0) map[1][i]--;
        if(map[R][i] > 0) map[R][i]--;
    }

    for(int i=2; i<R; i++){
        if(map[i][1] > 0) map[i][1]--;
        if(map[i][C] > 0) map[i][C]--;
    }

}

//step5. 특정 자리 온도 검사

int chk_temp(){
    int cnt = 0;

    for(int i=1;i<=R;i++){
        for(int j=1;j<=C;j++){
            if(heat[i][j] == 5 && map[i][j] >= K) cnt++;
        }
    }
    
    if(chk_cnt == cnt) return 1;
    else return 0;
}

void solve(){

    int ans = 0;
    while(1){

        spread_heat();
        adjust_temp();
        sub_outline();
        ans++;
        if(ans > 100){
            cout<<101<<endl;
            return;
        }
        if(chk_temp()) break;

    }

       cout<<ans<<endl;
}

int main(){

    cin >> R >> C >> K;

    for(int i=1;i<=R;i++){
        for(int j=1;j<=C;j++){
            cin>>heat[i][j];
            if(heat[i][j] == 5) chk_cnt++;
        }
    }

    cin>>W;

    for(int i =0; i<W; i++){
        int y,x,c;
        cin>>y>>x>>c;
        //0 1 2 3 동 서 북 남
        if(c==0){
            wall[y][x][2] = 1;
            wall[y - 1][x][3] = 1;
        }
        else if(c==1){
            wall[y][x][0] = 1;
            wall[y][x + 1][1] = 1;
        }

    }

    solve();

    return 0;
}