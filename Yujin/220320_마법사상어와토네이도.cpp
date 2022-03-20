#include <iostream>
using namespace std;

int n;
int x, y;
int res;
int A[501][501];
int dx[4] = { -1,0,1,0 }; //ÁÂ ÇÏ ¿ì »ó
int dy[4] = { 0,1,0,-1 };

int pc[9] = { 2, 10, 7, 1, 5, 10, 7, 1, 2 };
int l[2][9] = { {-2,-1,-1,-1,0,1,1,1,2}, {0,-1,0,1,-2,-1,0,1,0} };
int r[2][9] = { {-2,-1,-1,-1,0,1,1,1,2},{0,1,0,-1,2,1,0,-1,0} };
int u[2][9] = { {0,-1,0,1,-2,-1,0,1,0},{-2,-1,-1,-1,0,1,1,1,2} };
int d[2][9] = { {0,1,0,-1,2,1,0,-1,0},{-2,-1,-1,-1,0,1,1,1,2} };

void tornado() {
	for (int i = 1; i <= n - 1; i++) {
		if (i % 2 == 1) { //ÁÂ, ÇÏ
			for (int j = 0; j < i; j++) { //ÁÂ
				x += dx[0];
				y += dy[0];
				int val = A[y][x];
				for (int k = 0; k < 9; k++) {
					int ny = y + l[0][k];
					int nx = x + l[1][k];
					int spread = A[y][x] * pc[k] / 100;
					if (ny < 1 || nx < 1 || nx > n || ny > n) {
						res += spread;
					}
					else {
						A[ny][nx] += spread;
					}
					val -= spread;
				}

				A[y][x] = 0;
				int ny = y + dy[0];
				int nx = x + dx[0];
				if (ny >= 1 && nx >= 1 && nx <= n && ny <= n) A[ny][nx] += val;
				else res += val;
			}

			for (int j = 0; j < i; j++) { //ÇÏ
				x += dx[1];
				y += dy[1];
				int val = A[y][x];
				for (int k = 0; k < 9; k++) {
					int ny = y + d[0][k];
					int nx = x + d[1][k];
					int spread = A[y][x] * pc[k] / 100;
					if (ny < 1 || nx < 1 || nx > n || ny > n) {
						res += spread;
					}
					else {
						A[ny][nx] += spread;
					}
					val -= spread;
				}
				A[y][x] = 0;
				int ny = y + dy[1];
				int nx = x + dx[1];
				if (ny >= 1 && nx >= 1 && nx <= n && ny <= n) A[ny][nx] += val;
				else res += val;
			}
		}
		if (i % 2 == 0) { //¿ì, »ó
			for (int j = 0; j < i; j++) { //¿ì
				x += dx[2];
				y += dy[2];
				int val = A[y][x];
				for (int k = 0; k < 9; k++) {
					int ny = y + r[0][k];
					int nx = x + r[1][k];
					int spread = A[y][x] * pc[k] / 100;
					if (ny < 1 || nx < 1 || nx > n || ny > n) {
						res += spread;
					}
					else {
						A[ny][nx] += spread;
					}
					val -= spread;
				}
				A[y][x] = 0;
				int ny = y + dy[2];
				int nx = x + dx[2];
				if (ny >= 1 && nx >= 1 && nx <= n && ny <= n) A[ny][nx] += val;
				else res += val;
			}
			for (int j = 0; j < i; j++) { //»ó
				x += dx[3];
				y += dy[3];
				int val = A[y][x];
				for (int k = 0; k < 9; k++) {
					int ny = y + u[0][k];
					int nx = x + u[1][k];
					int spread = A[y][x] * pc[k] / 100;
					if (ny < 1 || nx < 1 || nx > n || ny > n) {
						res += spread;
					}
					else {
						A[ny][nx] += spread;
					}
					val -= spread;
				}
				A[y][x] = 0;
				int ny = y + dy[3];
				int nx = x + dx[3];
				if (ny >= 1 && nx >= 1 && nx <= n && ny <= n) A[ny][nx] += val;
				else res += val;
			}
		}
		if (i == n - 1) {//¸¶Áö¸· ÁÂ
			for (int j = 0; j < i; j++) { //ÁÂ
				x += dx[0];
				y += dy[0];
				int val = A[y][x];
				for (int k = 0; k < 9; k++) {
					int ny = y + l[0][k];
					int nx = x + l[1][k];
					int spread = A[y][x] * pc[k] / 100;
					if (ny < 1 || nx < 1 || nx > n || ny > n) {
						res += spread;
					}
					else {
						A[ny][nx] += spread;
					}
					val -= spread;
				}
				A[y][x] = 0;
				int ny = y + dy[0];
				int nx = x + dx[0];
				if (ny >= 1 && nx >= 1 && nx <= n && ny <= n) A[ny][nx] += val;
				else res += val;
			}
		}
	}
}

int main() {

	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> A[i][j];
		}
	}
	y = n / 2 + 1;
	x = n / 2 + 1;
	tornado();
	cout << res << "\n";
	return 0;
}