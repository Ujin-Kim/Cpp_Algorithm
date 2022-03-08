#include <iostream>
#include <vector>
#include <memory.h>
using namespace std;
#define MAX 101

int N,K;
int fish_ball[MAX]={};
int ball_stack[MAX][MAX]={};

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

void rotate_stack(){

    int rotate_ball[MAX][MAX]={};
    memcpy(rotate_ball,ball_stack,sizeof(ball_stack));

    while(1){
        int b_y = 0;
        int b_x = 0;

        for(int i=0;i<N;i++){
            if(rotate_ball[0][i] != 0){
                b_y = i;
                break;
            }
        }
        for(int i=N-1; i >=0;i--){
            if(rotate_ball[i][b_y] != 0){
                b_x = i;
                break;
            }
        }
        if(rotate_ball[N-1][b_x] == 0){
            break;
        }
        else{
            memcpy(ball_stack,rotate_ball,sizeof(rotate_ball));
            int temp[MAX] = {};
            int last[MAX] = {};
            int cnt = 0;
            int lcnt = 0;
            for(int i=b_y;i<N;i++){
                for(int j=0;j<b_x;j++){
                    temp[cnt++] = rotate_ball[i][j];
                }
            }
            for(int i=b_x + 1; i<N;i++){
                last[lcnt++] = rotate_ball[N-1][i];
            }

            memset(rotate_ball,0,sizeof(rotate_ball));

            for(int i=0;i<lcnt;i++){
                rotate_ball[N-1][i] = last[i];
            }
            
        }
    }
}

//step2. 어항 쌓아서 90도 돌리기 
void stack_ball(){
    int temp[MAX][MAX]={};

    memcpy(temp,ball_stack,sizeof(ball_stack));
    //맨 왼쪽 그 오른쪽 위에 올리기
    for(int i = 0; i<N - 1; i++){
        ball_stack[i][N-1] = fish_ball[i + 1];
    }
    ball_stack[0][MAX - 2] = fish_ball[0];

    //가장 왼쪽에 있는 블록들 오른쪽 90도로 돌린 후 위로 올리기
   rotate_stack();


} 
int main(){

    cin>>N>>K;

    for(int i=0;i<N;i++){
        cin>>fish_ball[i];
    }


    return 0;
}