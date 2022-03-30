#include <iostream>
#include <memory.h>
#include <queue>
using namespace std;
#define MAX 51

int N,M,T;

struct Node{

    int x,d,k;
};

struct Info{
    int y,x;
};

int circle[MAX][MAX]={};
int dir[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
queue<Node> que;
void Rotate(int d, int n){
    if(d==0){ //시계방향

        for(int y=1; y<=N; y++){
            
            if( y % n != 0) continue;
            
            int last = circle[y][M];
            for(int x = M - 1 ; x>=1; x--){

                circle[y][x + 1] = circle[y][x];

            }
            circle[y][1] = last;
        }

    }
    else if(d==1){
        for(int y=1; y<=N; y++){
            
            if( y % n != 0) continue;
            
            int first = circle[y][1];
            for(int x = 2 ; x <= M; x++){

                circle[y][x - 1] = circle[y][x];

            }
            circle[y][M] = first;
        }
    }
}

void chk_remove(){

    int map[MAX][MAX] ={};
    memcpy(map,circle,sizeof(circle));
    int chk = 0;
    int sum = 0;
    int cnt = 0;
    queue<Info> qinfo;
    for(int y=1; y<=N; y++){
        for(int x=1; x<=M; x++){
            if(circle[y][x] == -1) continue;
            
            qinfo.push({y,x});
        }
    }

    while(!qinfo.empty()){
        int y = qinfo.front().y;
        int x = qinfo.front().x;
        qinfo.pop();

        for(int i=0;i<4;i++){
            int ny = y+dir[i][0];
            int nx = x+dir[i][1];

            if(nx < 1) nx = M;
            if(nx > M) nx = 1;

            if((ny >= 1 && ny <=N )&& circle[y][x] == circle[ny][nx]){
                map[ny][nx] = -1;
                map[y][x] = -1;
                chk = 1;
            }
        }
    }

    memcpy(circle,map,sizeof(map));

    if(chk == 0){
        for(int y=1; y<=N; y++){
            for(int x=1; x<=M; x++){
                if(circle[y][x] == -1) continue;
                sum+=circle[y][x];
                cnt++;
            }
        }

        double avg = (double)sum/(double)cnt;

        for(int y=1; y<=N; y++){
            for(int x=1; x<=M; x++){
                if(circle[y][x] == -1) continue;

                if((double)circle[y][x] > avg) circle[y][x]--;
                else if((double)circle[y][x] < avg) circle[y][x]++;
            }
        }

    }


}


void solve(){

    for(int i=0; i<T; i++){
        int x = que.front().x;
        int d = que.front().d;
        int k = que.front().k;
        que.pop();

        for(int j=0; j<k; j++){
            Rotate(d,x);
        }
        chk_remove();
    }

    int ans = 0;

    for(int y=1; y<=N; y++){
        for(int x = 1; x<=M; x++){
            if(circle[y][x]==-1) continue;
            ans+=circle[y][x];
        }
    }

    cout<<ans<<"\n";

}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>N>>M>>T;

    for(int y=1; y<=N; y++){
        for(int x=1; x<=M; x++){
            cin>>circle[y][x];
        }
    }

    for(int i=0; i<T; i++){
        int x,d,k;
        cin >> x >> d >> k;
        que.push({x,d,k});
    }

    solve();

    return 0;
}