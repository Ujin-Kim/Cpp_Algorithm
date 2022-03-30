#include <iostream>
#include <vector>
#include <memory.h>
#include <queue>
using namespace std;

#define MAX 21

int N;
int city[MAX][MAX]={};
int map[MAX][MAX]={};
int dir[4][2] ={{0,-1},{0,1},{1,0},{-1,0}};
vector<int> dist;
vector<int> axis;
int ans = 999999999;

int isInfive(int y, int x , int d1, int d2, int ry, int rx){
    if( y > ry && y<ry+d1+d2&& x>=rx-d1 && x<=rx+d2) return true;
    return false;
}

void gary(int y, int x, int d1, int d2){

    int sum_sec[6] = {};

    memset(map,0,sizeof(map));

    for(int i=0; i<=d1; i++){
        map[y+i][x-i] = 5;
    }
    for(int i = 0; i<=d2;i++){
        map[y+i][x+i] = 5;

    }
    for(int i=0; i<=d1; i++){
        map[y+d2+i][x+d2-i]= 5;
    }

    for(int i=0; i<=d2; i++){
        map[y+d1+i][x-d1+i] = 5;
    }


    for(int i=y+1; i<y+d1+d2; i++){
        int chk1_y = 0;
        int chk1_x = 0;
        int chk2_y = 0;
        int chk2_x = 0;
        for(int j=x-d1; j<=x+d2; j++){
            if(map[i][j] == 5){
                if(chk1_y == 0) {
                    chk1_y = i;
                    chk1_x = j; 
                }
                else{
                    chk2_y = i;
                    chk2_x = j;
                    break;
                }
            }
        }
        for(int j = chk1_y; j<=chk2_y; j++){
            for(int k=chk1_x; k<=chk2_x; k++){
                map[j][k] = 5;
            }
        }
    }
    
  
    for(int i=1; i<y+d1; i++){
        for(int j=1;j<=x;j++){
            if(map[i-1][j] == 5 || map[i][j-1]==5) continue;
            if(map[i][j] == 0){
                map[i][j] = 1;
            }
        }
    }

      for(int i=1; i<=y+d2; i++){
        for(int j=x+1;j<=N;j++){
            if(map[i-1][j] ==5 || map[i][j+1] == 5) continue;
            if(map[i][j] == 0){
                map[i][j] = 2;
            }
        }
    }

      for(int i=y+d1; i<=N; i++){
        for(int j=1;j<x-d1+d2;j++){
            if(map[i+1][j] == 5 || map[i][j-1] ==5) continue;
            if(map[i][j] == 0){
                map[i][j] = 3;
            }
        }
    }

    for(int i=y+d2+1; i<=N; i++){
        for(int j=x+d2-d1; j<=N; j++){
            if(map[i][j]==0){
                map[i][j]=4;
            }
        }
    }

    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            sum_sec[map[i][j]] += city[i][j];
        }
    }

   int max_sum = -9999999;
   int min_sum = 99999999;


   for(int i=1; i<=5; i++){
       if(max_sum < sum_sec[i]) max_sum = sum_sec[i];
       if(min_sum > sum_sec[i]) min_sum = sum_sec[i];
   }
    

   if(ans > max_sum - min_sum){
       ans = max_sum - min_sum;
   }

}

void find_axis(int br , int d1, int d2){

    if(br == 2){

        int y = axis[0];
        int x = axis[1];

        if(y + d1 + d2 > N) return;
        if(x - d1 < 1 || x + d2 > N ) return;

        gary(y,x,d1,d2);

        return;
    }

    for(int i=1; i<=N; i++){
        axis.push_back(i);
        find_axis(br + 1, d1, d2);
        axis.pop_back();
    }
}

void permu(int br){
    if(br == 2){
        int d1 = dist[0];
        int d2 = dist[1];

        if(d1 + d2 >= N) return;

        find_axis(0,d1,d2);

        return;
    }

    for(int i=1; i<=N; i++){
        dist.push_back(i);
        permu(br+1);
        dist.pop_back();
    }
}

void solve(){

    permu(0);

    cout<<ans<<"\n";
}

int main(){

    cin >> N;

    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            cin>>city[y][x];
        }
    }

    solve();

    return 0;
}