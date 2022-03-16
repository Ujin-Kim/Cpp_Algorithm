#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

struct info {
	int d;
	int s;
};
int n, m;
int A[51][51];
int visited[51][51];
int dy[9] = {0,0,-1,-1,-1,0,1,1,1};
int dx[9] = {0,-1,-1,0,1,1,1,0,-1};
vector<info> mov;
vector<pair<int, int> > cloud; 

void move_cloud(int dir, int size) {
	for (int i = 0; i < cloud.size(); i++) {
		int y = cloud[i].first;
		int x = cloud[i].second;

		for (int s = 0; s < size; s++) {
			y += dy[dir];
			x += dx[dir];
			if (y == n + 1) y = 1;
			else if (y == 0) y = n;
			if (x == n + 1) x = 1;
			else if (x == 0) x = n;
		}

		cloud[i].first = y;
		cloud[i].second = x;
	}
}

void rainy() {
	for (int i = 0; i < cloud.size(); i++) {
		int y = cloud[i].first;
		int x = cloud[i].second;
		A[y][x] += 1;
		visited[y][x] = 1;
	}
}

void remove_cloud() {
	cloud.clear();
}

void copy_bug() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (visited[i][j] == 1) {
				//대각선 확인
				int cnt = 0;
				for (int k = 2; k < 9; k += 2) {
					int ny = i + dy[k];
					int nx = j + dx[k];
					if (1 > ny || ny > n || 1 > nx || nx > n) continue;
					if (A[ny][nx] > 0) cnt++;
				}
				A[i][j] += cnt;
			}
		}
	}
}

void make_cloud() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (visited[i][j] != 1 && A[i][j] >= 2) {
				cloud.push_back({ i, j });
				A[i][j] -= 2;
			}
		}
	}
	memset(visited, 0, sizeof(visited));
}

int main() {

	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> A[i][j];
		}
	}
	for (int i = 0; i < m; i++) {
		int d = 0, s = 0;
		cin >> d >> s;
		mov.push_back({ d,s });
	}

	//비바라기 시전
	cloud.push_back({ n, 1 });
	cloud.push_back({ n-1, 1 });
	cloud.push_back({ n, 2 });
	cloud.push_back({ n-1, 2 });

	//이동
	for (int t = 0; t < m; t++) {
		int d = mov[t].d;
		int s = mov[t].s;
		move_cloud(d, s);
		rainy();
		remove_cloud();
		copy_bug();
		make_cloud();
	}

	int res = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			res += A[i][j];
		}
	}
	cout << res << "\n";
	return 0;
}