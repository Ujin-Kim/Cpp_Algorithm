    #include <iostream>
    #include <memory.h>
    #include <vector>
    #include <algorithm>
    #include <queue>
    using namespace std;
    #define MAX 21

    int dir[5][2] = {{0,0},{-1,0},{1,0},{0,-1},{0,1}};
    int map[MAX][MAX];
    int N,M,K;
    int s_move[401][5][5]={};
    vector<int> shark[MAX][MAX]={};
    int start_dir[401]={};
    int cnt = 0;

    struct Node{
        int y,x,n,d;
    };

    struct Smell{
        int n = 0,k = 0;
    };

    int isInside(int y, int x){
        if(y < 1 || y > N || x < 1 || x > N) return 0;
        return 1;
    }

    Smell smell[MAX][MAX] = {};

    void set_smell(){

        for(int y=1; y<=N; y++){
            for(int x=1; x<=N; x++){
                
                if(!shark[y][x].empty()){
                    smell[y][x].n = shark[y][x][0];
                    smell[y][x].k = K;
                }
            }
        }

    }

    void move_shark(){

        queue<Node> que;
        vector<int> shark2[MAX][MAX];
        
        for(int y = 1; y <= N; y++){
            for(int x = 1; x <= N; x++){
                if(shark[y][x].empty()) continue;
                que.push({y,x,shark[y][x][0],start_dir[shark[y][x][0]]});
                shark[y][x].pop_back();
            }
        }

        while(!que.empty()){
            int y =que.front().y;
            int x = que.front().x;
            int n = que.front().n;
            int d = que.front().d;

            que.pop();
            
            int chk = 0;
            for(int i=1; i<=4; i++){
                int ny = y + dir[s_move[n][d][i]][0];
                int nx = x + dir[s_move[n][d][i]][1];

                if(!isInside(ny,nx)) continue;

                if(smell[ny][nx].k == 0){
                    shark2[ny][nx].push_back(n);
                    start_dir[n] = s_move[n][d][i];
                    chk = 1;
                    break;
                }

            }

            if(!chk){
                for(int i = 1; i<= 4; i++){
                    int ny = y + dir[s_move[n][d][i]][0];
                    int nx = x + dir[s_move[n][d][i]][1];

                    if(!isInside(ny,nx)) continue;

                    if(smell[ny][nx].n == n){
                        shark2[ny][nx].push_back(n);
                        start_dir[n] = s_move[n][d][i];
                        break;
                    }
                }
            }
        }

        for(int y =1; y<= N; y++){
            for(int x=1; x<=N; x++){
                if(smell[y][x].k > 0) smell[y][x].k--;
                shark[y][x] = shark2[y][x];
            }
        }

    }

    void delete_big(){
        for(int y=1; y<=N; y++){
            for(int x=1; x<=N; x++){
                if(shark[y][x].size() > 1){
                    sort(shark[y][x].begin(), shark[y][x].end());
                 
                    cnt = cnt - shark[y][x].size() + 1;

                    while(shark[y][x].size() > 1){
                        shark[y][x].pop_back();
                    }
                }
            }
        }
    }

    void solve(){
        int time = 0;

        while(1){
            time++;

            set_smell();
            move_shark();
            delete_big();
            if(cnt == 1) break;
            if(time == 1000 && cnt > 1){
                cout<<-1<<"\n";
                return;
            }
        }

        cout<<time<<"\n";
    }

    int main(){

        ios::sync_with_stdio(false);
        cin.tie(NULL);

        cin >> N >> M >> K;

        cnt = M;

        for(int y=1; y<=N; y++){
            for(int x=1; x<=N; x++){
               int n;
               cin>>n;
               if(n!=0){
                   shark[y][x].push_back(n);
               }
            }
        }
        for(int i=1; i<=M; i++){
            int d;
            cin >> d;
            start_dir[i] = d;
        }

        for(int i=1; i<=M; i++){
            for(int j=1;j<=4;j++){
                for(int k=1;k<=4;k++){
                    int d;
                    cin>>d;
                    s_move[i][j][k] = d;
                }
            }
        }

        solve();

        return 0;
    }