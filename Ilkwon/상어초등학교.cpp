    #include <iostream>
    #include <queue>
    #include <memory.h>
    using namespace std;
    #define MAX 21

    int N;
    int map[MAX][MAX]={};
    int visited[MAX][MAX]={};
    int ans = 0;
    vector<int> fav_friend[MAX*MAX];
    int score[5] = {0,1,10,100,1000};
    int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

    int isInside(int y, int x){
        if(y < 1 || y > N || x < 1 || x > N) return 0;
        return 1;
    }

    struct Friend{
        int y = -1,x = -1;
        int z_cnt = 0;
        int f_cnt = 0;
    };

    struct Node{
        int y, x;
        int cnt =0;
    };

    void find_loc(int n){

        Friend f_st;

        for(int y = 1; y <= N; y++){
            for(int x = 1; x <= N; x++){
                int t_cnt = 0;
                int f_cnt = 0;
                if(map[y][x] != 0 ) continue;
                for(int k =0; k<4; k++){
                    int ny = y + dir[k][0];
                    int nx = x + dir[k][1];

                    if(!isInside(ny,nx)) continue;
                    if(map[ny][nx] == 0) t_cnt++;
                    else{
                        for(int i = 1; i <=4; i++){
                            if(map[ny][nx] == fav_friend[n][i])f_cnt++;
                        }
                    }
                }
                if(f_st.f_cnt  < f_cnt){
                    f_st.y = y;
                    f_st.x = x;
                    f_st.f_cnt = f_cnt;
                    f_st.z_cnt = t_cnt;
                } else if(f_st.f_cnt == f_cnt){
                    if(f_st.z_cnt < t_cnt){
                        f_st.y = y;
                        f_st.x = x;
                        f_st.f_cnt = f_cnt;
                        f_st.z_cnt = t_cnt;
                    }
                    else if(f_st.z_cnt == t_cnt){
                        if(f_st.y == -1 && f_st.x == -1){
                            f_st.y = y;
                            f_st.x = x;
                        }
                    }
                }
            }
        }
        map[f_st.y][f_st.x] = fav_friend[n][0];

    }

    void cal_sc(int y, int x){

        int cnt = 0;
        int n = 0;
        for(int i=0;i<N*N; i++){
            if(map[y][x] == fav_friend[i][0]){
                n = i;
                break;
            }
        }
        
        for(int i=0;i<4;i++){
            int ny = y+dir[i][0];
            int nx = x+dir[i][1];

            if(!isInside(ny,nx)) continue;

            for(int j =1; j<5; j++){
                if(map[ny][nx] == fav_friend[n][j]) cnt++;
            }
        }

        ans += score[cnt];
    }
    void solve(){

        for(int i = 0; i< N*N; i++){

            find_loc(i);
        
        }


            for(int y =1; y<=N;y++){
                for(int x=1;x<=N; x++){
                    cal_sc(y,x);
                }
            }
        cout<<ans<<endl;

    }
    
    int main(){

        cin>>N;

        for(int i=0;i<N*N;i++){
            for(int j=0;j<5;j++){
                int n;
                cin>>n;
                fav_friend[i].push_back(n);
            }
        }

        solve();


        return 0;
    }