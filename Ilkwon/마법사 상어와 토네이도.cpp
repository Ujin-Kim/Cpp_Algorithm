#include <iostream>
using namespace std;
#define MAX 500

int N;
int map[MAX][MAX]={};
int mid = 0;
int dir[4][2] ={{0,-1},{1,0},{0,1},{-1,0}};
int s_dir[4][9][2] = {
{{-1,1},{1,1},{-1,0},{1,0},{-1,-1},{1,-1},{0,-2},{-2,0},{2,0}},
{{-1,-1},{-1,1},{0,-1},{0,1},{1,-1},{1,1},{2,0},{0,-2},{0,2}},
{{-1,-1},{1,-1},{-1,0},{1,0},{-1,1},{1,1},{0,2},{-2,0},{2,0}},
{{1,-1},{1,1},{0,-1},{0,1},{-1,-1},{-1,1},{-2,0},{0,-2},{0,2}}};
int sand_ratio[9]={1,1,7,7,10,10,5,2,2};
int ans = 0;

int isInside(int y, int x){
    if( y < 1 || y > N || x < 1 || x > N) return 0;
    return 1;
}

void move(){
    int t_y = mid;
    int t_x = mid;

    int d = 0;
    for(int i=1; i<=N; i++){
        if(t_y == 1 && t_x == 1) break;
        for(int j=0;j<2;j++){
             if(t_y == 1 && t_x == 1) break;
        for(int k = 1; k<= i; k++){
            t_y += dir[d][0];
            t_x += dir[d][1];
           int sand = map[t_y][t_x];
           int temp = sand;

           for(int x=0; x<9; x++){
               int ny = t_y + s_dir[d][x][0];
               int nx = t_x + s_dir[d][x][1];

               if(!isInside(ny,nx)){
                   ans += ((temp *  sand_ratio[x]) / 100);
                   sand -= ((temp *  sand_ratio[x]) / 100);
                   continue; 
               }
               else{
                   map[ny][nx] += ((temp * sand_ratio[x])/100);
                   sand -= ((temp *  sand_ratio[x]) / 100);
               }
             }
             int ny = t_y + dir[d][0];
             int nx = t_x + dir[d][1];

             if(!isInside(ny,nx)){
                ans += sand;
             } 
             else map[ny][nx] += sand;
              map[t_y][t_x] = 0;
              
              if(t_y == 1 && t_x == 1) break;
            }

           d++;
           if(d==4) d = 0;
        }
    }
}

void solve(){
    move();

    cout<<ans<<"\n";
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>N;    

    for(int y =1; y<=N; y++){
        for(int x =1; x<=N; x++){
            cin>>map[y][x];
        }
    }

    mid = (N+1)/2;

    solve();

    return 0;
}