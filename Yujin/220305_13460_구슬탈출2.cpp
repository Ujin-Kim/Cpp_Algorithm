#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct info {
	int rx, ry, bx, by, cnt;
};

int n, m;
int answer = -1;
char map[11][11];
bool visited[11][11][11][11]; //rx, ry, bx, by
queue<info> q;
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

void bfs() {
	while (!q.empty()) {
		int rx = q.front().rx;
		int ry = q.front().ry;
		int bx = q.front().bx;
		int by = q.front().by;
		int cnt = q.front().cnt;
		q.pop();

		if (cnt >= 10) {
			return;
		}

		for (int i = 0; i < 4; i++) {
			int nrx = rx;
			int nry = ry;
			int nbx = bx;
			int nby = by;
			int rc = 0;
			int bc = 0;
			int ncnt = cnt + 1;

			while (map[nrx + dx[i]][nry + dy[i]] != '#' && map[nrx][nry] != 'O') {
				nrx += dx[i];
				nry += dy[i];
				rc += 1; //빨간공이 움직인 횟수
			}
			while (map[nbx + dx[i]][nby + dy[i]] != '#' && map[nbx][nby] != 'O') {
				nbx += dx[i];
				nby += dy[i];
				bc += 1; //파란공이 움직인 횟수
			}

			//예제7번
			if (map[nbx][nby] == 'O') continue;
			if (map[nrx][nry] == 'O') {
				answer = ncnt;
				return;
			}

			//R,B가 같은 위치에 있으면 덜 움직인걸 다시 뒤로 보낸다
			if (nrx == nbx && nry == nby) {
				if (rc > bc) {
					nrx -= dx[i];
					nry -= dy[i];
				}
				else {
					nbx -= dx[i];
					nby -= dy[i];
				}
			}

			if (!visited[nrx][nry][nbx][nby]) {
				visited[nrx][nry][nbx][nby] = true;
				q.push({ nrx, nry, nbx, nby, ncnt });
			}
		}
	}
}


int main() {

	int rx = 0, ry = 0, bx = 0, by = 0;

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		string str = "";
		cin >> str;
		for (int j = 0; j < m; j++) {
			map[i][j] = str[j];
			if (str[j] == 'R') {
				rx = i;
				ry = j;
			}
			if (str[j] == 'B') {
				bx = i;
				by = j;
			}
		}
	}

	q.push({ rx, ry, bx, by, 0 });
	visited[rx][ry][bx][by] = true;
	bfs();

	cout << answer;

	return 0;
}