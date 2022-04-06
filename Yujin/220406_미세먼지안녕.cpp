#include <iostream>
using namespace std;

int r, c, t;
int up = 0;
int down = 0;
int map[51][51];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

void spread() {
	int new_map[51][51] = { 0, };
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			if (map[i][j] == -1) continue;
			int cnt = 0;
			int y = i;
			int x = j;
			int munzi = map[y][x];
			for (int k = 0; k < 4; k++) {
				int ny = y + dy[k];
				int nx = x + dx[k];
				if (ny < 1 || nx < 1 || ny > r || nx > c) continue;
				if (map[ny][nx] == -1) continue;
				cnt++;
				new_map[ny][nx] += munzi / 5;
			}
			new_map[y][x] += munzi - (munzi / 5) * cnt;
		}
	}
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			map[i][j] = new_map[i][j];
		}
	}
	map[up][1] = -1;
	map[down][1] = -1;
}

void wind() {
	for (int i = up - 2; i >= 1; i--) {
		map[i+1][1] = map[i][1];
	}
	for (int i = 2; i <= c; i++) {
		map[1][i - 1] = map[1][i];
	}
	for (int i = 2; i <= up; i++) {
		map[i-1][c] = map[i][c];
	}
	for (int i = c-1; i > 1; i--) {
		map[up][i + 1] = map[up][i];
	}
	map[up][2] = 0;

	for (int i = down + 2; i <= r; i++) {
		map[i-1][1] = map[i][1];
	}
	for (int i = 2; i <= c; i++) {
		map[r][i - 1] = map[r][i];
	}
	for (int i = r-1; i >= down; i--) {
		map[i + 1][c] = map[i][c];
	}
	for (int i = c - 1; i > 1; i--) {
		map[down][i + 1] = map[down][i];
	}
	map[down][2] = 0;
}

int main() {

	cin >> r >> c >> t;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			cin >> map[i][j];
			if (map[i][j] == -1){
				if (up == 0) up = i;
				else down = i;
			}
		}
	}

	for (int tm = 1; tm <= t; tm++) {
		spread();
		wind();
	}


	int res = 0;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			if (map[i][j] > 0) res += map[i][j];
		}
	}

	cout << res << "\n";
	return 0;
}