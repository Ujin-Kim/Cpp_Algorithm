#include <iostream>
#include <vector>
using namespace std;
#define MAX 101

int N;
int dir[4][2]={{0,1},{-1,0},{0,-1},{1,0}};
int map[MAX][MAX]={};

int isInside(int y, int x){
    if(y<0||y>100||x<0||x>100) return 0;
    return 1;
}
int ans = 0;
vector<int> general;
int main(){

    cin>>N;

    for(int i=0; i<N; i++){
        int x,y,d,g;
        cin>>x>>y>>d>>g;

        general.clear();
        map[y][x] = 1;
        general.push_back(d);

        for(int j=0; j<g; j++){
            for(int k=general.size()-1; k>=0; k--){
                general.push_back((general[k]+1)%4);
            }
        }

        int ny = y;
        int nx = x;
        for(int j=0; j<general.size(); j++){
            int gd = general[j];

            ny += dir[gd][0];
            nx += dir[gd][1];

            if(!isInside(ny,nx)) continue;
            map[ny][nx] = 1;
        }

    }

    for(int y=0; y<=100; y++){
        for(int x=0; x<=100; x++){
            if(map[y][x]==1 && isInside(y,x+1) && map[y][x+1] == 1){
                if(isInside(y+1,x) && map[y+1][x] == 1 && isInside(y+1,x+1) && map[y+1][x+1] == 1)
                    ans++;
            }
        }
    }

    cout<<ans<<"\n";

    return 0;
}