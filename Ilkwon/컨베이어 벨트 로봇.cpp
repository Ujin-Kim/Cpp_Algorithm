#include <iostream>
#include <queue>
using namespace std;
#define MAX 202

int N,K;
int convair[MAX] = {};
int visit[MAX] = {};
queue<int> robot;
int start_ = 0;
int end_ = 0;

void move_convair(){
    start_--;
    end_--;

    if(start_ == 0) start_ = 2*N;
    if(end_ == 0) end_ = 2*N; 
}

void move_robot(){

    int sz = robot.size();

    for(int i=0;i<sz; i++){
        int cur = robot.front();
        robot.pop();
        if(cur == end_) {
            visit[cur] = 0;
            continue;
        }

        int next = cur + 1;

        if(next == 2*N + 1) next= 1;

        if(visit[next]== 0 && convair[next] > 0){
            convair[next]--;
            visit[cur] = 0;
            if(next == end_) continue;
            visit[next]=1;
            robot.push(next);
        }
        else{
            robot.push(cur);
        }
    }

}

void put_robot(){

    if(convair[start_] > 0 && visit[start_] == 0){
        convair[start_]--;
        visit[start_]=1;
        robot.push(start_);
    }

}

void solve(){
    int ans = 0;
    while(1){
        ans++;
        move_convair();
        move_robot();
        put_robot();

        int cnt = 0;
        for(int i=1; i<=2*N; i++){
            if(convair[i] == 0){
                cnt++;
            }
        }
        if(cnt >= K) break;
    }

    printf("%d\n",ans);
}


int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>N>>K;

    for(int i=1; i<=2*N; i++){
        cin>>convair[i];
    }
    start_ = 1;
    end_ = N;

    solve();

    return 0;
}