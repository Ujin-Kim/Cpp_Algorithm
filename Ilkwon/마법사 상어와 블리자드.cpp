#include <iostream>
#include <memory.h>
#include <queue>
using namespace std;
#define MAX 50

int dir[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
//0 1 2 3 북 남 서 동
int d_dir[4] = {2,1,3,0};
int map[MAX][MAX] = {};
int N, M;
int shark;
int zero_cnt = 0;
int ans = 0;
struct Dir{
    int d,s;
};
//서 남 동 북 순으로 이동
//2 1 3 0 순으로 이동

struct Info{
    int y, x, sc;
};

struct Block{
    int n,cnt;
};
queue<Dir> dque;

int isInside(int y, int x){
    if(y < 1 || y > N || x < 1 || x > N) return 0;
    return 1;
}

//step1. 폭탄
void boom(int d, int s){

    int y = (N+1)/2;
    int x = (N+1)/2;

    for(int i=0;i<s;i++){
        y += dir[d][0];
        x += dir[d][1];

        if(isInside(y,x)){
            map[y][x] = 0;
            zero_cnt++;
        }
    }
}
//step2. 빈칸이동
void move(){

    //서 남  동 북  순으로 이동
    int y = (N+1)/2;
    int x = (N+1)/2;
    int d = d_dir[0];

    int cur = 0;
    for(int i = 1; i<=N; i++){
        for(int j=0; j<2; j++){
            d = d_dir[cur];
            for(int k=1; k<=i; k++){
                int prev = map[y][x];
                int prev_y = y;
                int prev_x = x;

                y += dir[d][0];
                x += dir[d][1];

                if(!isInside(y,x) || (prev_y == (N+1)/2 && prev_x == (N+1)/2)) continue;

                if(map[prev_y][prev_x] == 0){
                    map[prev_y][prev_x] = map[y][x];
                    map[y][x] = 0;
                }
            }
            cur++;
            if(cur == 4) cur = 0;
        }
    }
}

//step3. 연속되는 구슬 폭발
void chain_boom(){
    int y = (N+1)/2;
    int x = (N+1)/2;
    int d = d_dir[0];
    queue<Info> que;

    int cur = 0;

    for(int i = 1; i<=N; i++){
        for(int j=0; j<2; j++){
            d = d_dir[cur];
            for(int k=1; k<=i; k++){

                int prev = map[y][x];
                int prev_y = y;
                int prev_x = x;

                y+=dir[d][0];
                x+=dir[d][1];

                if(!isInside(y,x)) continue;
                if(isInside(y,x) && prev!=0 && prev == map[y][x]){
                    que.push({prev_y,prev_x,map[y][x]});
                }
                else{
                    que.push({prev_y,prev_x,prev});
                   if(que.size() >= 4){
                       int tn = que.front().sc;
                       int sz = que.size();

                       while(!que.empty()){
                           int qy = que.front().y;
                           int qx = que.front().x;
                           que.pop();
                           
                           map[qy][qx] = 0;
                           zero_cnt++;
                       }
                       ans += (tn * sz);
                   }
                   if(!que.empty()){
                       while(!que.empty()) que.pop(); 
                   }
                }

            }
            cur++;
            if(cur == 4) cur = 0;
        }
    }
}

int search_chain(){
    int y = (N+1)/2;
    int x = (N+1)/2;
    int d = d_dir[0];

    int cur = 0;
    int cnt = 1;
    int chk = 0;
    for(int i = 1; i<=N; i++){
        for(int j=0; j<2; j++){
            d = d_dir[cur];
            for(int k=1; k<=i; k++){
                int prev = map[y][x];
                int prev_y = y;
                int prev_x = x;

                y += dir[d][0];
                x += dir[d][1];

                if(!isInside(y,x)) continue;

                if(isInside(y,x) && prev!=0 && prev == map[y][x]){
                    cnt++;
                if(cnt == 4){
                    chk = 1;
                    break;
                }
                }
                else cnt = 1;
            }
            if(chk) break;
            cur++;
            if(cur == 4) cur = 0;
        }
        if(chk) break;
    }
    return chk;
}

//step4. 블록 재정비
void reloc_block(){
    queue<Block> que;
    int y = (N+1)/2;
    int x = (N+1)/2;
    int d = d_dir[0];

    int cur = 0;
    int cnt = 1;

    for(int i = 1; i<=N; i++){
        for(int j=0; j<2; j++){
            d = d_dir[cur];
            for(int k=1; k<=i; k++){
                int prev = map[y][x];
                int prev_y = y;
                int prev_x = x;

                y += dir[d][0];
                x += dir[d][1];

                if(!isInside(y,x)) continue;

                if(isInside(y,x) && prev!=0 && prev == map[y][x]){
                    cnt++;
                }
               else if(prev!=0 && prev != map[y][x]){
                   que.push({prev,cnt});
                   cnt=1;
               }
            }
            cur++;
            if(cur == 4) cur = 0;
        }
    }

    memset(map,0,sizeof(map));

     y = (N+1)/2;
     x = (N+1)/2;
     d = d_dir[0];

     cur = 0;
     cnt = 0;
    for(int i = 1; i<=N; i++){
        for(int j=0; j<2; j++){
            d = d_dir[cur];
            for(int k=1; k<=i; k++){
                cnt++;
                y += dir[d][0];
                x += dir[d][1];
                
                if(!isInside(y,x)) continue;
                if(que.empty()) return;
               if(cnt%2 != 0){
                   map[y][x] = que.front().cnt;
               }
               else if(cnt%2 == 0){
                   map[y][x] = que.front().n;
                   que.pop();
               }
            }
            cur++;
            if(cur == 4) cur = 0;
        }
    }

}
void solve(){
    for(int i=0;i<M;i++){
        boom(dque.front().d, dque.front().s);
        dque.pop();

        while(zero_cnt != 0){
            move();
            zero_cnt--;
        }

        while(search_chain()){
            chain_boom();
            while(zero_cnt != 0){
                move();
                zero_cnt--;
            }
        }
        reloc_block();
    }

    cout<<ans<<endl;
}
int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>N>>M;

    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            cin>>map[i][j];
        }
    }

    for(int i=0;i<M;i++){
        int d,s;

        cin>>d>>s;
        dque.push({d-1,s});
    }

    solve();


    return 0;
}