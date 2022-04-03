#include <iostream>
#include <vector>
using namespace std;

struct info {
	int dir;
	int x;
	int y;
	bool alive; //1살아있음 0죽음
};

struct node {
	int x;
	int y;
	int d;
};

int dx[8] = { -1,-1,-1,0,1,1,1,0 };
int dy[8] = { 1,0,-1,-1,-1,0,1,1 };
int max_res;

void shark_move(vector<vector<int> > map, vector<info> fish, node shark, int res, int ex, int ey) {

	int sy = shark.y;
	int sx = shark.x;
	shark.y = ey;
	shark.x = ex;
	int num = map[ex][ey];
	shark.d = fish[num].dir;
	fish[map[ex][ey]].alive = 0;
	res += map[ex][ey];
	map[sx][sy] = 0; //0상어가 머물렀던 자리 0으로
	map[ex][ey] = -1; //-1 새로운 상어칸

	//fish_move()
	for (int i = 1; i < fish.size(); i++) {
		if (fish[i].alive == 0) continue;
		int d = fish[i].dir;
		int x = fish[i].x;
		int y = fish[i].y;

		for (int j = 0; j < 8; j++) {
			int dd = d + j;
			if (dd >= 8) dd -= 8;
			int nx = x + dx[dd];
			int ny = y + dy[dd];

			if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4) continue;
			if (map[nx][ny] == -1) continue;

			fish[i].dir = dd;
			if (map[nx][ny] == 0) {//빈칸이면
				map[x][y] = 0;
				map[nx][ny] = i;
				fish[i].y = ny;
				fish[i].x = nx;
			}
			else if (map[nx][ny] >= 1) {//다른 물고기 칸이면
				int tmp = 0;

				tmp = fish[map[nx][ny]].y;
				fish[map[nx][ny]].y = fish[i].y;
				fish[i].y = tmp;

				tmp = fish[map[nx][ny]].x;
				fish[map[nx][ny]].x = fish[i].x;
				fish[i].x = tmp;

				tmp = map[nx][ny];
				map[nx][ny] = map[x][y];
				map[x][y] = tmp;

			}
			break;
		}
	}

	//shark_move()
	int y = shark.y;
	int x = shark.x;
	int d = shark.d;

	for (int i = 1; i <= 3; i++) {
		int ny = y + dy[d] * i;
		int nx = x + dx[d] * i;

		if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4) continue;
		if (map[nx][ny] == 0) continue;
		shark_move(map, fish, shark, res, nx, ny);
	}

	if (max_res < res) max_res = res;
	return;
}

int main() {

	vector<vector<int> > map(5);
	vector<info> fish(20);
	node shark = { 0,0,0 };

	//input
	fish[0] = { 0,0,0,0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int a = 0, b = 0;
			cin >> a >> b;
			map[i].push_back(a);
			fish[a] = { b,i, j,1 };
		}
	}

	//start
	int res = 0;

	shark_move(map, fish, shark, res, 0, 0);

	cout << max_res << "\n";

	return 0;
}