#include <iostream>
#include <cmath>
#include <queue>
using namespace std;

int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
int N,M;
char board[10][10]={};
//빨간 구슬과 파란 구슬 두개가 존재

struct Node{
    int ry,rx,by,bx,lev=0;
};
Node node;


int visited[10][10][10][10]={};
int boardGame(){
    
    queue<Node> que;
    int rlev = -1;
    que.push(node);

    visited[node.ry][node.rx][node.by][node.bx]=1;

    while(!que.empty()){
      
        Node cur = que.front();
        que.pop();

        if(board[cur.ry][cur.rx]=='O' && board[cur.by][cur.bx]!='O') {
            rlev = cur.lev;
            break;
        }    
        if(cur.lev > 10) break;

        for(int i=0; i<4;i++){
            int nry = cur.ry; 
            int nrx = cur.rx;

            int nby = cur.by;
            int nbx = cur.bx;

            while(1){
                if(board[nry][nrx] != '#' && board[nry][nrx] != 'O'){
                    nry += dir[i][0];
                    nrx += dir[i][1];
                }
                else {
                        if(board[nry][nrx] == '#'){
                        nry -= dir[i][0];
                        nrx -= dir[i][1];
                        }
                    break;
                }
            }

            while(1){
                if(board[nby][nbx] != '#' && board[nby][nbx] != 'O'){
                    nby += dir[i][0];
                    nbx += dir[i][1];
                }
                else{
                    if(board[nby][nbx]=='#'){
                        nby -= dir[i][0];
                        nbx -= dir[i][1];
                    }
                    break;
                }
            }

            if(nry == nby && nrx == nbx){
                if(board[nry][nrx] != 'O'){
                int rdist = abs(cur.ry - nry) + abs(cur.rx - nrx);
                int bdist = abs(cur.by - nby) + abs(cur.bx - nbx);

                if(rdist > bdist){
                    nry -= dir[i][0];
                    nrx -= dir[i][1];
                }
                else{
                    nby -= dir[i][0];
                    nbx -= dir[i][1];
                }
                }
            }

            if(visited[nry][nrx][nby][nbx] == 0){
                visited[nry][nrx][nby][nbx] = 1;

                Node temp;
                temp.ry = nry;
                temp.rx = nrx;
                temp.by = nby;
                temp.bx = nbx;
                temp.lev = cur.lev + 1;
                que.push(temp);
            }

        }
    }
    return rlev;
}

int main(){

   cin>>N>>M;

   for(int i=0;i<N;i++){
       for(int j=0;j<M;j++){
           cin>>board[i][j];
           if(board[i][j]=='R'){
               node.ry = i;
               node.rx = j;
           }
           if(board[i][j]=='B'){
               node.by = i;
               node.bx = j;
           }
       }
   }
    cout << boardGame() << endl;

    return 0;
}