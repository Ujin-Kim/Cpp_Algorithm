#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int n;
int t;
int baby_x;
int baby_y;
int baby_size = 2;
int eat;
int map[21][21];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
struct info {
	int y;
	int x;
	int cnt;
};
bool cmp(info front, info back)
{
	if (front.cnt == back.cnt) {
		if (front.y == back.y) {
			return front.x < back.x;
		}
		return front.y < back.y;
	}
	return front.cnt < back.cnt;
}
vector<info> eat_list;

bool bfs() {
	int visited[21][21] = {0,};
	queue<info> q;
	q.push({ baby_y, baby_x, 0 });
	visited[baby_y][baby_x] = 1;
	bool flag = false;

	while (!q.empty()) {
		int y = q.front().y;
		int x = q.front().x;
		int c = q.front().cnt;
		q.pop();

		if (map[y][x] < baby_size && map[y][x] != 0) {
			flag = true;
			eat_list.push_back({ y, x, c });
		}

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny < 1 || nx < 1 || ny > n || nx > n) continue;
			if (map[ny][nx] > baby_size) continue;
			if (visited[ny][nx]) continue;
			visited[ny][nx] = 1;
			q.push({ ny, nx, c+1 });
		}
	}

	return flag;
}

int main() {

	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				baby_y = i;
				baby_x = j;
				map[i][j] = 0;
			}
		}
	}

	while (1) {
		//가까운 물고기 먹으러가기
		eat_list.clear();
		if (bfs() == false) break;
		else {
			sort(eat_list.begin(), eat_list.end(), cmp);
			baby_y = eat_list[0].y;
			baby_x = eat_list[0].x;
			map[baby_y][baby_x] = 0;
			t += eat_list[0].cnt;
			eat++;
			if (eat == baby_size) {
				baby_size++;
				eat = 0;
			}
		}
	}
	cout << t << "\n";
	return 0;
}