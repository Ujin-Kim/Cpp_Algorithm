#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

struct node {
	int m;
	int d;
	int s;
};

int n, m, k;
int dy[8] = {-1,-1,0,1,1,1,0,-1};
int dx[8] = {0,1,1,1,0,-1,-1,-1};
vector<node> map[51][51];
vector<node> map2[51][51];

void move() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map2[i][j].clear();
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int l = 0; l < map[i][j].size(); l++) {
				int y = i;
				int x = j;
				int m = map[i][j][l].m;
				int d = map[i][j][l].d;
				int s = map[i][j][l].s;

				for (int size = 0; size < s; size++) {
					y += dy[d];
					x += dx[d];
					if (y == 0) y = n;
					else if (y == n + 1) y = 1;
					if (x == 0) x = n;
					else if (x == n + 1) x = 1;
				}
				map2[y][x].push_back({ m, d, s });
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[i][j] = map2[i][j];
		}
	}
}

void div() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map2[i][j].clear();
		}
	}
	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {
			if (map[r][c].empty()) continue;
			else if (map[r][c].size() == 1) {
				map2[r][c] = map[r][c];
			}
			else if (map[r][c].size() >= 2) {
				int cnt = map[r][c].size();
				int total_m = 0;
				int total_s = 0;
				int odd = 0;
				int even = 0;
				for (int i = 0; i < cnt; i++) {
					if (map[r][c][i].d % 2 == 0) even++;
					else odd++;
					total_m += map[r][c][i].m;
					total_s += map[r][c][i].s;
				}
				//질량 0 이면 삭제
				if (total_m / 5 == 0) continue;
				if (odd == cnt || even == cnt) {
					map2[r][c].push_back({ total_m / 5, 0, total_s / cnt });
					map2[r][c].push_back({ total_m / 5, 2, total_s / cnt });
					map2[r][c].push_back({ total_m / 5, 4, total_s / cnt });
					map2[r][c].push_back({ total_m / 5, 6, total_s / cnt });
				}
				else {
					map2[r][c].push_back({ total_m / 5, 1, total_s / cnt });
					map2[r][c].push_back({ total_m / 5, 3, total_s / cnt });
					map2[r][c].push_back({ total_m / 5, 5, total_s / cnt });
					map2[r][c].push_back({ total_m / 5, 7, total_s / cnt });
				}
			}
			
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[i][j] = map2[i][j];
		}
	}
	int de = -1;
}

int main() {
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++) {
		int r = 0, c = 0, m = 0, s = 0, d = 0;
		cin >> r >> c >> m >> s >> d;
		map[r][c].push_back({ m, d, s });
	}

	for (int t = 0; t < k; t++) {
		//이동
		move();
		//2개 이상의 파이어볼
		div();
	}

	int res = 0;
	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {
			for (int l = 0; l < map[r][c].size(); l++) {
				res += map[r][c][l].m;
			}
		}
	}
	cout << res << "\n";
	return 0;
}