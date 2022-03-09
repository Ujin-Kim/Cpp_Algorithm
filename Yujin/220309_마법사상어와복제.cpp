#include <iostream>
#include <vector>
using namespace std;

int m, s;
int sx, sy;
int max_fish;
int dx[8] = { 0,-1,-1,-1,0,1,1,1 };
int dy[8] = { -1,-1,0,1,1,1,0,-1 };
int sdx[5] = { 0,-1,0,1,0 };
int sdy[5] = { 0,0,-1,0,1 };
int smell[5][5];
vector<int> fish[5][5];
vector<int> cfish[5][5];
vector<int> shark_move;
vector<int> shark_select;



void move_fish(int n) {
    vector<int> after_fish[5][5];
    for (int i = 1; i < 5; i++) {
        for (int j = 1; j < 5; j++) {
            for (int k = 0; k < fish[i][j].size(); k++) {
                int x = i;
                int y = j;
                int d = fish[i][j][k];

                bool flag = false;
                for (int l = 0; l < 8; l++) {
                    int nd = (8 + d - l) % 8;
                    int ny = y + dy[nd];
                    int nx = x + dx[nd];
                    if (ny < 1 || nx < 1 || ny >= 5 || nx >= 5) continue;
                    if (ny == sy && nx == sx) continue;
                    if (smell[nx][ny] != 0 && n - smell[nx][ny] <= 2) continue;
                    flag = true;
                    after_fish[nx][ny].push_back(nd);
                    break;
                }
                if (flag == false) {
                    after_fish[x][y].push_back(d);
                }
            }
        }
    }
    for (int i = 1; i < 5; i++) {
        for (int j = 1; j < 5; j++) {
            fish[i][j] = after_fish[i][j];
        }
    }
}

int shark_eat() {
    bool visit[5][5] = { false, };
    int res = 0;
    int nsy = sy;
    int nsx = sx;
    for (int i = 0; i < shark_select.size(); i++) {
        nsx += sdx[shark_select[i]];
        nsy += sdy[shark_select[i]];
        
        if (nsy < 1 || nsx < 1 || nsy >= 5 || nsx >= 5) return -1;
        if (!visit[nsx][nsy]) {
            visit[nsx][nsy] = true;
            res += fish[nsx][nsy].size();
        }
    }
    return res;
}

void dfs() {
    if (shark_select.size() == 3) {
        int cnt = shark_eat();
        if (cnt > max_fish) {
            max_fish = cnt;
            shark_move = shark_select;
        }
        return;
    }
    for (int i = 1; i <= 4; i++) {
        shark_select.push_back(i);
        dfs();
        shark_select.pop_back();
    }
}

void move_shark(int n) {
    for (int i = 0; i < shark_move.size(); i++) {
        sy += sdy[shark_move[i]];
        sx += sdx[shark_move[i]];
        if (fish[sx][sy].size() != 0) {
            fish[sx][sy].clear();
            smell[sx][sy] = n;
        }
    }
}

void copy_magic() {
    for (int i = 1; i < 5; i++) {
        for (int j = 1; j < 5; j++) {
            for (int d = 0; d < cfish[i][j].size(); d++) {
                fish[i][j].push_back(cfish[i][j][d]);
            }
        }
    }
}

int main() {

    cin >> m >> s;
    for (int i = 0; i < m; i++) {
        int x = 0, y = 0, d = 0;
        cin >> x >> y >> d;
        fish[x][y].push_back(d - 1);
    }
    cin >> sx >> sy;

    for (int t = 1; t <= s; t++) {

        //1. 현재 물고기 위치 저장
        for (int i = 1; i < 5; i++) {
            for (int j = 1; j < 5; j++) {
                cfish[i][j] = fish[i][j];
            }
        }

        //2. 물고기 이동
        move_fish(t);

        //3. 물고기 가장 많이 먹을 수 있는 칸 찾기
        max_fish = -1;
        shark_select.clear();
        dfs();

        //4. 상어 이동
        move_shark(t);

        //5. 물고기 복제
        copy_magic();
    }

    // 남은 물고기 수 
    int res = 0;
    for (int i = 1; i < 5; i++) {
        for (int j = 1; j < 5; j++) {
            res += fish[i][j].size();
        }
    }
    cout << res;
    return 0;
}