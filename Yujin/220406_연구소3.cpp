#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct info {
	int y;
	int x;
};

int n, m; //연구소의 크기, 바이러스의 개수 
int map[51][51]; //0빈칸, 1벽, 2바이러스
int sec[51][51];
vector<info> virus;
vector<info> s_virus;
queue<info> q;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
bool visited[51][51];
int result = 987654321;

void bfs() {
	while (!q.empty()) {
		int y = q.front().y;
		int x = q.front().x;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
			//벽일때 
			if (map[ny][nx] == 1) continue;
			//비활성화 바이러스가 있지도 않고, 빈칸인 곳만 
			if (sec[ny][nx] == -1) {
				//시간 ++ 
				sec[ny][nx] = sec[y][x] + 1;
				q.push({ ny, nx });
			}
		}
	}

	//빈공간이 있는지 check
	bool check = true;
	int maxtime = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 0) { //처음에 빈칸이었고 
				if (sec[i][j] == -1) { //바이러스가 안퍼졌으면 
					check = false;
					break;
				}
				else {
					maxtime = max(maxtime, sec[i][j]);
				}
			}
		}
	}

	if (check) {
		result = min(maxtime, result);
	}
}

void selection(int idx, int cnt) {
	if (cnt == m) {
		//q에 선택한 virus 넣기 
		for (int i = 0; i < m; i++) {
			q.push({ s_virus[i].y, s_virus[i].x });
		}

		//sec배열 초기화
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				sec[i][j] = -1;
			}
		}

		//선택된 virus의 sec는 0으로 변경
		for (int i = 0; i < m; i++) {
			sec[s_virus[i].y][s_virus[i].x] = 0;
		}

		bfs();

		return;
	}
	for (int i = idx; i < virus.size(); i++) {
		s_virus.push_back({ virus[i].y, virus[i].x });
		selection(i + 1, cnt + 1);
		s_virus.pop_back();
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) virus.push_back({ i, j });
		}
	}
	//m개 선택
	selection(0, 0);

	if (result == 987654321) result = -1;
	cout << result << "\n";

	return 0;
}