#include <iostream>
#include <vector>
using namespace std;
#define MAX 13

int N,K;
int map[MAX][MAX] = {};
int dir[5][2] = {{0,0},{0,1},{0,-1},{-1,0},{1,0}};
struct Node{
    int y,x;
};
struct Info{
    int n,d;
};
vector<Info> vec[MAX][MAX];
Node chess[11];
vector<Info> temp;
vector<Info> rest;
int ans = 0;

int isInside(int y, int x){
    if(y<1 || y>N || x<1 || x>N) return 0;
    return 1;
}

void move(){

    temp.clear();
    rest.clear();

    for(int i=1; i<=K; i++){
        int y = chess[i].y;
        int x = chess[i].x;

        temp.clear();
        rest.clear();

        int chk = 0;
        for(int j=0; j<vec[y][x].size(); j++){
            if(chk) temp.push_back({vec[y][x][j].n,vec[y][x][j].d});
            else if(vec[y][x][j].n == i){
                temp.push_back({vec[y][x][j].n,vec[y][x][j].d});
                chk = 1;
            }
            else{
                rest.push_back({vec[y][x][j].n,vec[y][x][j].d});
            }
        }
        vec[y][x].clear();
        
        for(int j=0; j<rest.size(); j++)
            vec[y][x].push_back({rest[j].n,rest[j].d});

        int d = temp.front().d;

        int ny = y + dir[d][0];
        int nx = x + dir[d][1];

        int sz = temp.size();

        if(!isInside(ny,nx)){
            if(d==1) d=2;
            else if(d==2) d=1;
            else if(d==3) d=4;
            else if(d==4) d=3;

            ny = y + dir[d][0];
            nx = x + dir[d][1];

            if(!isInside(ny,nx)){
                cout<<-1<<"\n";
                exit(0);
            }

            if(map[ny][nx]==2){
                
                vec[y][x].push_back({i,d});
                for(int j=1; j<sz; j++){
                    vec[y][x].push_back({temp[j].n,temp[j].d});
                }

                if(vec[y][x].size() >=4){
                    cout<<ans<<"\n";
                    exit(0);
                }
            }
            else if(map[ny][nx] == 1){
                for(int j = sz-1; j>0; j--){
                    vec[ny][nx].push_back({temp[j].n,temp[j].d});
                    chess[temp[j].n].y = ny;
                    chess[temp[j].n].x = nx;
                }
                chess[i].y = ny;
                chess[i].x = nx;

                 vec[ny][nx].push_back({i,d});

                 if(vec[ny][nx].size() >= 4){
                     cout<<ans<<"\n";
                     exit(0);
                 }
            }
            else if(map[ny][nx] == 0){
                chess[i].y = ny;
                chess[i].x = nx;
                vec[ny][nx].push_back({i,d});
                for(int j=1;j<sz;j++){
                    vec[ny][nx].push_back({temp[j].n,temp[j].d});
                    chess[temp[j].n].y = ny;
                    chess[temp[j].n].x = nx;
                }

                if(vec[ny][nx].size() >= 4){
                    cout<<ans<<"\n";
                    exit(0);
                }
            }
        }
        else{
            if(map[ny][nx] == 0){
                for(int j=0;j<sz;j++){
                    vec[ny][nx].push_back({temp[j].n,temp[j].d});
                    chess[temp[j].n].y = ny;
                    chess[temp[j].n].x = nx;
                }
                if(vec[ny][nx].size() >= 4){
                    cout<<ans<<"\n";
                    exit(0);
                }
            }
            else if(map[ny][nx] == 1){
                for(int j=sz-1; j>=0; j--){
                    vec[ny][nx].push_back({temp[j].n,temp[j].d});
                    chess[temp[j].n].y = ny;
                    chess[temp[j].n].x = nx;
                }

                if(vec[ny][nx].size() >=4){
                    cout<<ans<<"\n";
                    exit(0);
                }
            }
            else if(map[ny][nx]==2){
                if(d==1) d=2;
                else if(d==2) d=1;
                else if(d==3) d=4;
                else if(d==4) d=3;

                ny = y+dir[d][0];
                nx = x+dir[d][1];

                if(!isInside(ny,nx) || map[ny][nx] == 2){

                    vec[y][x].push_back({i,d});
                    for(int j=1;j<sz;j++){
                        vec[y][x].push_back({temp[j].n,temp[j].d});
                    }
                    if(vec[y][x].size() >= 4){
                        cout<<ans<<"\n";
                        exit(0);
                    }
                }
                else if(map[ny][nx] == 1){
                    for(int j = sz-1; j>0; j--){
                    vec[ny][nx].push_back({temp[j].n,temp[j].d});
                    chess[temp[j].n].y = ny;
                    chess[temp[j].n].x = nx;
                }
                    chess[i].y = ny;
                    chess[i].x = nx;

                 vec[ny][nx].push_back({i,d}); 
                
                    if(vec[ny][nx].size() >=4){
                        cout<<ans<<"\n";
                        exit(0);
                    }
                }

                else if(map[ny][nx] == 0){
                    vec[ny][nx].push_back({i,d});
                    chess[i].y = ny;
                    chess[i].x = nx;
                    for(int j=1;j<sz;j++){
                        vec[ny][nx].push_back({temp[j].n,temp[j].d});
                        chess[temp[j].n].y = ny;
                        chess[temp[j].n].x = nx;
                    }
                     if(vec[ny][nx].size() >=4){
                        cout<<ans<<"\n";
                        exit(0);
                    }
                }
            }
        }

    }

}

void solve(){
 
    while(1){
        
        ans++;
        if(ans > 1000){
            cout<<-1<<"\n";
            return;
        }
        
        move();

    }

}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>N>>K;

    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            cin>>map[y][x];
        }
    }

    for(int i=1;i<=K;i++){
        int y,x,d;
        cin>>y>>x>>d;
        vec[y][x].push_back({i,d});
        chess[i].y=y;
        chess[i].x=x;
    }

    solve();

    return 0;
}