#include <iostream>
#include <memory.h>
using namespace std;

int N;
int board[20][20]={};
int dir_sel[5]={};
int temp[20][20]={};
int ans = 0;
void move_up(){

    for(int x = 0; x < N; x++){
        for(int y = 0; y < N - 1; y++){
            if(board[y][x] == 0){
                for(int k = y + 1; k < N; k++){
                    if(board[k][x] != 0){
                        board[y][x] = board[k][x];
                        board[k][x] = 0;
                        break;
                    }
                }
            }
        }
    }
    for(int x=0;x<N;x++){
        for(int y=0; y < N - 1; y++){
            if(board[y][x] != 0 && board[y][x] == board[y + 1][x]){
                board[y][x] *= 2;
                board[y + 1][x]=0;
            }
        }
    }
     for(int x = 0; x < N; x++){
        for(int y = 0; y < N - 1; y++){
            if(board[y][x] == 0){
                for(int k = y + 1; k < N; k++){
                    if(board[k][x] != 0){
                        board[y][x] = board[k][x];
                        board[k][x] = 0;
                        break;
                    }
                }
            }
        }
    }
}   

void move_left(){

    for(int y = 0; y < N; y++){
        for(int x = 0; x < N - 1; x++){
            if(board[y][x] == 0){
                for(int k = x + 1; k < N; k++){
                    if(board[y][k] != 0){
                        board[y][x] = board[y][k];
                        board[y][k] = 0;
                        break;
                    }
                }
            }
        }
    }
    for(int y=0;y<N;y++){
        for(int x=0;x < N - 1;x++){
            if(board[y][x] != 0 && board[y][x] == board[y][x + 1]){
                board[y][x] *= 2;
                board[y][x+1]=0;
            }
        }
    }
     for(int y = 0; y < N; y++){
        for(int x = 0; x < N - 1; x++){
            if(board[y][x] == 0){
                for(int k = x + 1; k < N; k++){
                    if(board[y][k] != 0){
                        board[y][x] = board[y][k];
                        board[y][k] = 0;
                        break;
                    }
                }
            }
        }
    }
}

void move_down(){

    for(int x = 0; x < N; x++){
        for(int y = N - 1; y > 0; y--){
            if(board[y][x] == 0){
                for(int k = y - 1; k >= 0; k--){
                    if(board[k][x] != 0){
                        board[y][x] = board[k][x];
                        board[k][x] = 0;
                        break;
                    }
                }
            }
        }
    }

    for(int x=0;x<N;x++){
        for(int y=N-1;y>0;y--){
            if(board[y][x] != 0 && board[y][x] == board[y - 1][x]){
                board[y][x] *= 2;
                board[y - 1][x]=0;
            }
        }
    }

    for(int x = 0; x < N; x++){
        for(int y = N - 1; y > 0; y--){
            if(board[y][x] == 0){
                for(int k = y - 1; k >= 0; k--){
                    if(board[k][x] != 0){
                        board[y][x] = board[k][x];
                        board[k][x] = 0;
                        break;
                    }
                }
            }
        }
    }
}

void move_right(){

    for(int y = 0; y < N; y++){
        for(int x = N-1; x > 0; x--){
            if(board[y][x] == 0){
                for(int k = x - 1; k >= 0; k--){
                    if(board[y][k] != 0){
                        board[y][x] = board[y][k];
                        board[y][k] = 0;
                        break;
                    }
                }
            }
        }
    }

    for(int y=0;y<N;y++){
        for(int x=N-1;x>0;x--){
            if(board[y][x] != 0 && board[y][x] == board[y][x - 1]){
                board[y][x] *= 2;
                board[y][x-1]=0;
            }
        }
    }

    for(int y = 0; y < N; y++){
        for(int x = N-1; x > 0; x--){
            if(board[y][x] == 0){
                for(int k = x - 1; k >= 0; k--){
                    if(board[y][k] != 0){
                        board[y][x] = board[y][k];
                        board[y][k] = 0;
                        break;
                    }
                }
            }
        }
    }

}

void game(){
    for(int i=0;i<5;i++){
        int sel = dir_sel[i];
        if(sel == 0) move_up();
        if(sel == 1) move_left();
        if(sel == 2) move_down();
        if(sel == 3) move_right();
    }
    int Max = -99999999;
    for(int y=0;y<N;y++){
        for(int x = 0; x<N; x++){
            if(Max < board[y][x]) Max = board[y][x];
        }
    }

    if(ans < Max) ans = Max;
}

void dfs(int lev){

    if(lev == 5){
        memcpy(board,temp,sizeof(temp));
        game();
        return;
    }
    memcpy(temp,board,sizeof(board));
    for(int i=0; i<4; i++){
        dir_sel[lev] = i;
        dfs(lev + 1);
        memcpy(board,temp,sizeof(temp));
    }

}
int main(){

    cin>>N;

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>board[i][j];
        }
    }

    dfs(0);

    cout<<ans<<endl;

    return 0;
}