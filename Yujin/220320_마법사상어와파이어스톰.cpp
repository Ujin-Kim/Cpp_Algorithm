#include <iostream>
#include <math.h>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

int n, q;
int border;
int A[65][65];
int AA[65][65];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
vector<int> order;

void rotation(int y, int x, int l) {
	int c = 0;
	for (int i = y; i < y + l; i++) {
		queue<int> line;
		for (int j = x; j < x + l; j++) {
			line.push(A[i][j]);
		}
		for (int j = y; j < y + l; j++) {
			AA[j][x + l - 1 - c] = line.front();
			line.pop();
		}
		c++;
	}
}

void check() {
	memcpy(AA, A, sizeof(A));
	for (int i = 0; i < border; i++) {
		for (int j = 0; j < border; j++) {
			int cnt = 0;
			if (A[i][j] == 0) continue;
			for (int k = 0; k < 4; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];

				if (ny < 0 || ny >= border || nx < 0 || nx >= border) continue;
				if (A[ny][nx] > 0) cnt++;
			}
			if (cnt < 3) AA[i][j] -= 1;
		}
	}
	int de = -1;
	memcpy(A, AA, sizeof(AA));
}

void magic(int l) {
	//회전
	memset(AA, 0, sizeof(AA));
	for (int y = 0; y < border; y += l) {
		for (int x = 0; x < border; x += l) {
			rotation(y, x, l);
		}
	}
	memcpy(A, AA, sizeof(A));
	//3개이상의 얼음이 있는 칸과 인접하지 않으면 -1
	check();
}

int bfs() {
	int res2 = 0;
	int visited[65][65] = { 0 };
	for (int i = 0; i < border; i++) {
		for (int j = 0; j < border; j++) {
			if (visited[i][j] == 1) continue;
			if (A[i][j] == 0) continue;

			queue<pair<int, int> > que;
			int cnt = 1;
			visited[i][j] = 1;
			que.push({ i, j });
			while(!que.empty()){
				int y = que.front().first;
				int x = que.front().second;
				que.pop();

				for (int k = 0; k < 4; k++) {
					int ny = y + dy[k];
					int nx = x + dx[k];
					if (ny < 0 || nx < 0 || ny >= border || nx >= border) continue;
					if (visited[ny][nx] == 1) continue;
					if (A[ny][nx] > 0) {
						cnt++;
						visited[ny][nx] = 1;
						que.push({ ny, nx });
					}
				}
			}
			if (res2 < cnt) res2 = cnt;
		}
	}
	return res2;
}

int main() {

	cin >> n >> q;
	border = pow(2, n);
	for (int i = 0; i < border; i++) {
		for (int j = 0; j < border; j++) {
			cin >> A[i][j];
		}
	}
	for (int i = 0; i < q; i++) {
		int x = 0;
		cin >> x;
		order.push_back(x);
	}

	for (int i = 0; i < q; i++) {
		int level = pow(2, order[i]);
		magic(level);
	}

	int res1 = 0;
	for (int i = 0; i < border; i++) {
		for (int j = 0; j < border; j++) {
			res1 += A[i][j];
		}
	}
	int res2 = bfs();

	cout << res1 << "\n";
	cout << res2 << "\n";
	return 0;
}