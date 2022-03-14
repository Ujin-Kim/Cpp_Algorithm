#include <iostream>
#include <queue>
#include <algorithm>
#include <string.h>
#include <stack>
using namespace std;

struct node {
	int cnt;
	int rainbow;
	int y;
	int x;
};

bool cmp(node front, node back) {
	if (front.cnt == back.cnt) {
		if (front.rainbow == back.rainbow) {
			if (front.y == back.y) {
				return front.x > back.x;
			}
			return front.y > back.y;
		}
		return front.rainbow > back.rainbow;
	}
	return front.cnt > back.cnt;
}

int n, m;
int res;
int map[21][21];
vector<node> selected;
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

void bfs(int y, int x) {
	int visited[21][21] = { 0, };
	int tar = map[y][x];
	map[y][x] = -2;
	visited[y][x] = 1;
	queue<pair<int, int> > q;
	q.push({ y, x });

	while (!q.empty()) {
		int yy = q.front().first;
		int xx = q.front().second;
		q.pop();

		for (int k = 0; k < 4; k++) {
			int ny = yy + dy[k];
			int nx = xx + dx[k];

			if (1 > ny || n < ny || 1 > nx || n < nx) continue;
			if (visited[ny][nx] == 1) continue;
			if (map[ny][nx] == -1) continue;
			if (map[ny][nx] == tar || map[ny][nx] == 0) {
				visited[ny][nx] = 1;
				q.push({ ny, nx });
				map[ny][nx] = -2; //제거
			}
		}
	}
}

int find_remove() {
	selected.clear();
	vector<pair<int, int> > rain;
	int visited[21][21] = { 0, };
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j] == 0) rain.push_back({ i, j });
		}
	}

	//find
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (visited[i][j] == 1) continue;
			if (1 <= map[i][j] && map[i][j] <= m) {
				int cnt = 1;
				int rainbow = 0;
				
				int tar = map[i][j];
				visited[i][j] = 1;
				queue<pair<int, int> > q;
				q.push({ i, j });

				while (!q.empty()) {
					int yy = q.front().first;
					int xx = q.front().second;
					q.pop();

					for (int k = 0; k < 4; k++) {
						int ny = yy + dy[k];
						int nx = xx + dx[k];

						if (1 > ny || n < ny || 1 > nx || n < nx) continue;
						if (map[ny][nx] == -1) continue;
						if (visited[ny][nx] == 1) continue; //무지개가 아니고, 방문했던 곳이면
						if (map[ny][nx] == tar || map[ny][nx] == 0) {
							visited[ny][nx] = 1;
							q.push({ ny, nx });
							cnt++;
							if (map[ny][nx] == 0) rainbow++;
						}
					}
				}
				if (cnt >= 2) selected.push_back({ cnt, rainbow, i, j });

				//무지개있는곳 visited 0으로 초기화
				for (int k = 0; k < rain.size(); k++) {
					visited[rain[k].first][rain[k].second] = 0;
				}
			}
		}
	}

	if (selected.size() == 0) return -1;

	//remove
	sort(selected.begin(), selected.end(), cmp);
	bfs(selected[0].y, selected[0].x);
	res += selected[0].cnt * selected[0].cnt;
	return 0;
}

void gravity() {
	for (int x = 1; x <= n; x++) {
		int cnt = 0;
		while (1) {
			cnt = 0;
			for (int y = n; y > 1; y--) {
				if (map[y][x] == -2 && map[y - 1][x] != -1 && map[y-1][x] != -2) map[y][x] = map[y - 1][x], map[y-1][x] = -2, cnt++;
			}
			if (cnt == 0) break;
		}
	}
}

void rotation() {
	int map2[21][21] = { 0, };
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			map2[n-x+1][y] = map[y][x];
		}
	}
	memcpy(map, map2, sizeof(map));
}

int main() {
	
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}

	while (1) {
		//블록그룹찾고 제거, 블록그룹 없으면 break;
		if (find_remove() == -1) break;
		gravity();
		rotation();
		gravity();
	}

	cout << res << "\n";
	return 0;
}