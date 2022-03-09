#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <memory.h>
using namespace std;
#define MAX 101

int N,K;
int fish_ball[MAX]={};
int ball_stack[MAX][MAX]={};
int dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};

int isInside(int y, int x){
    if(y < 0 || y>=N || x<0 || x>=N) return 0;
    return 1;
}

//step1. 가장 적은 수의 물고기를 찾고 1 더해주기
void find_min(){
    int Min = 9999999;

    for(int i=0;i<N;i++){
        if(fish_ball[i] < Min) Min = fish_ball[i];
    }

    for(int i=0;i<N;i++){
        if(fish_ball[i] == Min) fish_ball[i] ++;
    }
}

//step2. 90도로 돌리고 어항 쌓기
void rotate_stack(){

    int rotate_ball[MAX][MAX]={};
    memcpy(rotate_ball,ball_stack,sizeof(ball_stack));

    while(1){
        int b_y = 0;
        int b_x = 0;

        for(int i=0;i<N;i++){
            if(rotate_ball[i][0] != 0){
                b_y = i;
                break;
            }
        }
        for(int i=N-1; i >=0;i--){
            if(rotate_ball[b_y][i] != 0){
                b_x = i;
                break;
            }
        }
        if(rotate_ball[N-1][b_x] == 0){
            break;
        }
        else{
            memcpy(ball_stack,rotate_ball,sizeof(rotate_ball));
            int temp[MAX][MAX] = {};
            int last[MAX] = {};
            int ucnt = 0;
            int dcnt = 0;
            int lcnt = 0;
    

            for(int i=b_y;i<N;i++,ucnt++){
                for(int j=0;j<=b_x;j++){
                    temp[ucnt][j] = rotate_ball[i][j];
                }
            }

            for(int i=b_x + 1; i<N;i++){
                last[lcnt++] = rotate_ball[N-1][i];
            }

            memset(rotate_ball,0,sizeof(rotate_ball));

            for(int i=0;i<lcnt;i++){
                rotate_ball[N-1][i] = last[i];
            }
        
            for(int y = N-2, d = b_x; y>=N-2 - b_x; y--, d--){
                for(int x = 0, t = ucnt - 1; x<=N - b_y; x++, t--){
                    rotate_ball[y][x] = temp[t][d];
                }
            }
           
        }
    }
}

struct Node{
    int y,x;
    int fish;
};

//step3. 물고기 수 조정해주기
void nomalize_fish(){
    queue<Node> que;
    int temp[MAX][MAX] = {};

    memcpy(temp,ball_stack,sizeof(ball_stack));

    for(int i = 0; i<N; i++){
        for(int j=0;j<N;j++){
            if(ball_stack[i][j] != 0){
                que.push({i,j,ball_stack[i][j]});
            }
        }
    }

    while(!que.empty()){
        int y = que.front().y;
        int x = que.front().x;
        int fish = que.front().fish;
        que.pop();

        for(int i=0;i<4;i++){
            int ny = y + dir[i][0];
            int nx = x + dir[i][1];

            if(!isInside(ny,nx) || temp[ny][nx] == 0 ) continue; 
            int d = (fish - temp[ny][nx]) / 5;

            if(fish > temp[ny][nx] && d > 0){
                ball_stack[ny][nx] += d;
                ball_stack[y][x] -= d;
            }
        }
    }

 
}

//step4. 일자로 정렬하기

void line_ball(){

    int cnt = 0;
    for(int x = 0; x<N; x++){
        for(int y = N-1; y>=0; y--){
            if(ball_stack[y][x] == 0 )continue;
            fish_ball[cnt++] = ball_stack[y][x];
        }
    }
}

//step5. 밑 바닥이 N/4 될 때까지 나누기

void divide_4(){
    memset(ball_stack,0,sizeof(ball_stack));

    int nN = N / 2;

    int temp[MAX] = {};

    int cnt = 0;
    for(int x = nN - 1; x>=0; x--){
        temp[cnt++] = fish_ball[x];
    }

    for(int x = 0; x<nN; x++){
        ball_stack[N-1][x] = fish_ball[x + nN];
    }

    for(int x = 0; x<nN; x++){
        ball_stack[N-2][x] = temp[x];
    }
    //처음 올리기

    int left_fish[MAX][MAX] = {};

    nN/=2;
    int lx = 0;
    int ly = N-1;
    for(int y = N-2; y< N; y++, ly--){
        for(int x = nN-1, lx = 0; x>=0; x--){
            left_fish[ly][lx++] = ball_stack[y][x];
        }
    }

int right_fish[MAX][MAX] = {};

for(int y = N-2; y< N; y++){
    for(int x = 0; x<nN; x++){
        right_fish[y][x] = ball_stack[y][x+nN];
    }
}
memcpy(ball_stack,right_fish,sizeof(right_fish));

for(int y = N-4; y<N-2; y++){
    for(int x = 0; x<nN; x++){
        ball_stack[y][x] = left_fish[y+2][x];
    }
}
    
}

//step6. 물고기 차 구하기
int dis_fish(){

    int Max = -9999999;
    int Min = 9999999;

    for(int i=0;i<N;i++){
        if(Max < fish_ball[i]) Max = fish_ball[i];
        if(Min > fish_ball[i]) Min = fish_ball[i];
    }


    return Max - Min;
}

void stack_ball(){

int cnt = 0;
    while(1){
    cnt++;
    find_min();

    memset(ball_stack,0,sizeof(ball_stack));

    //맨 왼쪽 그 오른쪽 위에 올리기
    for(int i = 0; i<N - 1; i++){
        ball_stack[N-1][i] = fish_ball[i + 1];
    }
    ball_stack[N-2][0] = fish_ball[0];

    //가장 왼쪽에 있는 블록들 오른쪽 90도로 돌린 후 위로 올리기
   rotate_stack();

   nomalize_fish();

   line_ball();

   divide_4();

    nomalize_fish();

   line_ball();
    
    if(dis_fish() <= K) break;

  }

  cout<<cnt<<endl;

} 
int main(){

    cin>>N>>K;

    for(int i=0;i<N;i++){
        cin>>fish_ball[i];
    }

    stack_ball();

    return 0;
}
