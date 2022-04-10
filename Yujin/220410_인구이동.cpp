#include <iostream>
#include <vector>
using namespace std;

int n, l, r;
int result = 0;
int cnt, sum;
int A[51][51];
bool visited[51][51];
vector<pair<int, int>> visit;
int dx[4] = { 0,0,-1,1 }; //»óÇÏÁÂ¿ì 
int dy[4] = { -1,1,0,0 };

void dfs(int y, int x) {
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (!visited[ny][nx]) {
			if (ny >= 0 && ny < n && nx >= 0 && nx < n) {
				if (abs(A[ny][nx] - A[y][x]) >= l && abs(A[ny][nx] - A[y][x]) <= r) {
					visited[ny][nx] = 1;
					cnt++;
					sum += A[ny][nx];
					visit.push_back({ ny, nx });
					dfs(ny, nx);

				}
			}
		}
	}
}

int main() {
	cin >> n >> l >> r;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> A[i][j];
		}
	}

	while (1) {
		bool check = false;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				visited[i][j] = false;
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (!visited[i][j]) {
					visit.clear();
					cnt = 1;
					sum = A[i][j];
					visited[i][j] = 1;

					visit.push_back({ i, j });
					dfs(i, j);

					if (cnt >= 2) {
						check = true;
						int avr = sum / cnt;
						for (int k = 0; k < visit.size(); k++) {
							A[visit[k].first][visit[k].second] = avr;
						}
					}
				}
			}
		}

		if (check == false) break;
		else result++;
	}

	cout << result;

	return 0;
}