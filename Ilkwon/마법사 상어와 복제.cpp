#include <iostream>
#include <vector>
#include <memory.h>
using namespace std;

int f_dir[8][2]={{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1}};
int s_dir[4][2]={{-1,0},{0,-1},{1,0},{0,1}};

int move_shark[64][3]={};
struct Node{
    int d, visit;
};
vector<Node> fish[5][5];
vector<int> egg[5][5];
vector<int> temp;
int sz = 0;
int M,S;
int shark[5][5]={};
int dead[5][5]={};
int s_y, s_x;

int can_move(int y, int x){
    if(shark[y][x] == 1 || dead[y][x] != -1) return 0;
    return 1;
}
int isInside(int y, int x){
    if(y<1 || y>4 || x<1 || x>4) return 0;
    return 1;
}
void sel_sharkMoving(int lev){

    if(lev == 3){

        for(int i=0;i<3;i++){
            move_shark[sz][i] = temp[i];
        }
        sz++;
        return;
    }

    for(int i=0;i<4;i++){
        temp.push_back(i);
        sel_sharkMoving(lev+1);
        temp.pop_back();
    }
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    sel_sharkMoving(0);

    cin>>M>>S;

    for(int i=0;i<M;i++){
        int y,x,d;
        cin>>y>>x>>d;
        fish[y][x].push_back({d-1,0});
    }   

    cin>>s_y>>s_x;

    shark[s_y][s_x] = 1;

    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            dead[i][j] = -1;
        }
    }

    for(int cur = 1; cur<=S; cur++){
        //알 낳기
        for(int y=1;y<=4;y++){
            for(int x=1;x<=4;x++){
                if(!fish[y][x].empty()){
                    int n = fish[y][x].size();

                    for(int i=0;i<n;i++){
                        egg[y][x].push_back(fish[y][x][i].d);
                    }
                }
            }
        }

        //물고기 움직이기
        for(int y=1;y<=4;y++){
            for(int x=1;x<=4; x++){
                if(fish[y][x].empty()) continue;
                int n = fish[y][x].size();

                int change = 0;
                for(int i=0;i<n;i++){
                    if(fish[y][x][i].visit == 1) continue;
                    
                    int d = fish[y][x][i].d;
                    change = 1;
                    int ny = y + f_dir[d][0];
                    int nx = x + f_dir[d][1];
                    int cant = 0;
                    int orign_d = d;
                    while(!isInside(ny,nx) || !can_move(ny,nx)){
                        d-=1;
                        if(d<0) d=7;

                        ny = y + f_dir[d][0];
                        nx = x + f_dir[d][1];

                        if(orign_d == d){
                            cant=1;
                            break;
                        }
                    }
                    if(cant){
                        fish[y][x][i].visit = 1;
                    }
                    else{
                        fish[ny][nx].push_back({d,1});
                    }

                }
                if(change){
            
                vector<int> tp;
                for(int t =0; t<n; t++){
                    if(fish[y][x][t].visit == 1) tp.push_back(fish[y][x][t].d);
                }
                fish[y][x].clear();
                int t_sz = tp.size();
                if(t_sz ==0) continue;
                for(int t = 0; t<t_sz;t++){
                    fish[y][x].push_back({tp[t],1});
                }
                }
            }
        }

        //상어 움직이기
        int max_ = 0;
		int shark_y = 0;
		int shark_x = 0;
		int tp[5][5] = {};
		int eat[5][5] = {};

		for (int i = 0; i < 64; i++) {
			int food = 0;
			int ny = s_y;
			int nx = s_x;
			memset(tp, 0, sizeof(tp));

			for (int j = 0; j < 3; j++) {
				ny += s_dir[move_shark[i][j]][0];
				nx += s_dir[move_shark[i][j]][1];

				if(!isInside(ny, nx)) break;
				
				if(!fish[ny][nx].empty() && !tp[ny][nx]) {
					food += fish[ny][nx].size();
					tp[ny][nx] += fish[ny][nx].size();
				}
			}
			if(max_ < food && isInside(ny,nx)) {
				shark_y = ny;
				shark_x = nx;
				memcpy(eat, tp, sizeof(tp));
				max_ = food;
			}
		}

		if (max_ == 0) {
			for (int i = 0; i < 64; i++) {
				shark_y = s_y;
				shark_x = s_x;
				for (int j = 0; j < 3; j++) {
					shark_y += s_dir[move_shark[i][j]][0];
					shark_x += s_dir[move_shark[i][j]][1];
					if (!isInside(shark_y, shark_x)) break;
				}
				if (isInside(shark_y, shark_x)) break;
			}
		}

		shark[s_y][s_x] = 0;
		shark[shark_y][shark_x] = 1;
        s_y = shark_y;
        s_x = shark_x;
        //시체 처리

        for(int i=1;i<=4;i++){
            for(int j=1;j<=4;j++){
                if(eat[i][j] > 0){
                    dead[i][j] = cur;
                    fish[i][j].clear();
                }
            }
        }

        //냄새 처리

        for(int i=1;i<=4;i++){
            for(int j=1;j<=4;j++){
                if(dead[i][j] == -1) continue;

                if(cur - dead[i][j] == 2){
                    dead[i][j] = -1;
                }
            }
        }

        //알 낳기

        for(int y=1;y<=4;y++){
            for(int x=1;x<=4;x++){
                if(!fish[y][x].empty()){
                    int n = fish[y][x].size();

                    for(int k = 0; k<n; k++){
                        fish[y][x][k].visit = 0;
                    }
                }

                if(!egg[y][x].empty()){
                    int n = egg[y][x].size();

                    for(int k = 0; k<n; k++){
                        fish[y][x].push_back({egg[y][x][k],0});
                    }
                    egg[y][x].clear();
                }
            }
        }

    }

    int ans = 0;

    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            if(!fish[i][j].empty()){
                ans += fish[i][j].size();
            }
        }
    }
    cout<<ans<<endl;

    return 0;
}
