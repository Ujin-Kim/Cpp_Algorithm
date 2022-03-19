#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <memory.h>
using namespace std;
#define MAX 65

int N,Q;
int map[MAX][MAX]={};
vector<int> arrL;
int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
int max_ice = -99999999;
int ans = 0;
int visited[MAX][MAX] = {};
int i_cnt = 0;
int isInside(int y, int x){
    if(y<1 || y> N || x<1 || x> N) return 0;
    return 1;
}
void fire_storm(int s_y,int s_x,int l){

    int n = pow(2,l);

    if(n==1) return;

    int** temp = new int*[n];

    for(int i=0;i<n;i++)
        temp[i] = new int[n];

    for(int i=0, y=s_y; i<n; i++, y++){
        for(int j=0, x=s_x; j<n;j++, x++){
            temp[j][n-i-1] = map[y][x];
        }
    }

    for(int i=0,y=s_y;i<n;i++,y++){
        for(int j=0,x=s_x;j<n;j++,x++){
            map[y][x] = temp[i][j];
        }
    }

    for(int i=0; i<n;i++){
        delete[] temp[i];
    }
    delete[] temp;

}

void del_ice(){
    int temp[MAX][MAX]={};

    memcpy(temp,map,sizeof(map));

    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            int cnt = 0;

            if(temp[y][x] == 0) continue;

            for(int i=0;i<4;i++){
                int ny = y+dir[i][0];
                int nx = x+dir[i][1];

                if(!isInside(ny,nx)) continue;
                if(temp[ny][nx] > 0) cnt ++;
            }

            if(cnt < 3) map[y][x]--;
        }
    }
}

void dfs(int y, int x){
 
     if(max_ice < i_cnt) max_ice = i_cnt;
     
     visited[y][x] =1;

     for(int i=0;i<4;i++){
         int ny = y+dir[i][0];
         int nx = x+dir[i][1];

         if(!isInside(ny,nx) || visited[ny][nx] || map[ny][nx] == 0) continue;
         i_cnt++;
         dfs(ny,nx);
     }

}

void solve(){

    for(int i=0;i<arrL.size();i++){
        for(int y = 1; y<=N; y+=pow(2,arrL[i])){
            for(int x=1; x<=N; x+=pow(2,arrL[i])){
                fire_storm(y,x,arrL[i]);
            }
        }
        del_ice();
    }

    for(int y =1; y<=N; y++){
        for(int x=1;x<=N; x++){
            i_cnt = 1;
            if(visited[y][x]==0 && map[y][x] > 0) dfs(y,x);
            ans += map[y][x];
        }
    }

    cout<<ans<<endl;
    if(max_ice < 0) cout<<0<<endl;
    else cout<<max_ice<<endl;
}

int main(){

    cin >> N >> Q;

    N = pow(2,N);

    for(int y = 1; y <= N; y++){
        for(int x = 1; x <= N; x++){
            cin>>map[y][x];
        }
    }

    for(int i=0;i<Q;i++){
        int n;
        cin>>n;
        arrL.push_back(n);
    }

    solve();

    return 0;
}
