#include <iostream>
#include <vector>
using namespace std;
#define MAX 51

int N,M;
int ans = 9999999;
int map[MAX][MAX]={};
vector<pair<int,int>> chicken;
vector<pair<int,int>> house;
vector<pair<int,int>> temp;
int used[14] = {};

void dfs(int br, int next){
    if(br == M){
        int sum_ = 0;
        for(int i=0; i<house.size(); i++){
            int min_dist =999999;
            for(int j=0;j<temp.size(); j++){
                int dist = abs(house[i].first - temp[j].first) + abs(house[i].second - temp[j].second);
                if(min_dist > dist) min_dist = dist; 
            }
            sum_ += min_dist;
        }
       if(ans > sum_) ans = sum_;

        return;
    }

    for(int i=next;i<chicken.size();i++){
        if(used[i] == 1) continue;
        used[i] = 1;
        temp.push_back(chicken[i]);
        dfs(br+1,i);
        used[i] = 0;
        temp.pop_back();
    }

}

int main(){

    cin>>N>>M;

    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            cin>>map[y][x];
            if(map[y][x] == 1){
                house.push_back({y,x});
            }
            if(map[y][x]==2){
                chicken.push_back({y,x});
            }
        }
    }

    dfs(0,0);

    cout<<ans<<"\n";

    return 0;
}