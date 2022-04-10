#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX 11

int N,M,K;

vector<int> trees[MAX][MAX];
int A[MAX][MAX]={};
int map[MAX][MAX]={};
int dir[8][2]={{0,1},{0,-1},{1,0},{-1,0},{-1,-1},{-1,1},{1,-1},{1,1}};
int isInside(int y, int x){
    if(y<1 || y>N || x<1 || x>N) return 0;
    return 1;
}

void spring(){

    vector<int> tree2[MAX][MAX];

    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            if(trees[y][x].empty()) continue;

            int sz = trees[y][x].size();

            sort(trees[y][x].begin(), trees[y][x].end());
            
            int fertil = 0;
            for(int i=0; i<sz; i++){
                if(map[y][x] >= trees[y][x][i]){
                    map[y][x] -= trees[y][x][i];
                    trees[y][x][i]++;
                    tree2[y][x].push_back(trees[y][x][i]);
                } 
                else{
                    fertil+=trees[y][x][i]/2;
                }
            }

            map[y][x]+=fertil;

            trees[y][x] = tree2[y][x];
        }
    }
}

void fall(){

    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            if(trees[y][x].empty()) continue;

            int sz = trees[y][x].size();

            for(int i=0; i<sz; i++){
                if(trees[y][x][i] % 5 == 0){
                    for(int k=0; k<8; k++){
                        int ny = y + dir[k][0];
                        int nx = x + dir[k][1];

                        if(!isInside(ny,nx)) continue;

                        trees[ny][nx].push_back(1);
                    }
                }
            }
        }
    }
}

void winter(){

    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            map[y][x] += A[y][x];
        }
    }
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>N>>M>>K;

    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin>>A[i][j];
            map[i][j] = 5;
        }
    }

    for(int i=0; i<M; i++){
        int y,x,age;
        cin>>y>>x>>age;

        trees[y][x].push_back(age);
    }

    while(K--){
        //양분 먹기
        spring();

        //번식하기
        fall();

        //양분 더하기
        winter();
    }
    
    int ans = 0;

    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            ans += trees[y][x].size();
        }
    }

    cout<<ans<<"\n";

    return 0;
}