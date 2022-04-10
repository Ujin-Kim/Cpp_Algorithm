#include <iostream>
#include <vector>
using namespace std;

struct info {
	int y;
	int x;
	int speed;
	int dir;
	int size;
};

int r, c, m; //y,x,상어의 수 
int y, x, s, d, z;
int dx[5] = { 0,0,0,1,-1 }; //1위 2아래 3오른쪽 4왼쪽 
int dy[5] = { 0,-1,1,0,0 };
vector<info> shark[102][102];

int dir_change(int d) {
	if (d == 1) return 2;
	else if (d == 2) return 1;
	else if (d == 3) return 4;
	else return 3;
}

int main() {
	//input 
	cin >> r >> c >> m;
	for (int i = 0; i < m; i++) {
		cin >> y >> x >> s >> d >> z;
		if (d == 1 || d == 2) s %= ((r - 1) * 2);
		if (d == 3 || d == 4) s %= ((c - 1) * 2);
		shark[y][x].push_back({ y, x, s, d, z });
	}

	//start
	int result = 0;
	for (int king = 1; king <= c; king++) {
		//가장 가까운 상어 잡기
		for (int i = 1; i <= r; i++) {
			if (!shark[i][king].empty()) {
				result += shark[i][king][0].size;
				shark[i][king].pop_back();
				break;
			}
		}

		//상어 이동
		vector<info> newshark[102][102];
		for (int i = 1; i <= r; i++) {
			for (int j = 1; j <= c; j++) {
				if (!shark[i][j].empty()) {

					int ny = shark[i][j][0].y;
					int nx = shark[i][j][0].x;
					int ns = shark[i][j][0].speed;
					int nd = shark[i][j][0].dir;
					int nz = shark[i][j][0].size;

					int move = ns;
					while (move--) {
						int cny = ny + dy[nd];
						int cnx = nx + dx[nd];

						if (cny <= 0 || cnx <= 0 || cny > r || cnx > c) {
							nd = dir_change(nd);

							cny = ny + dy[nd];
							cnx = nx + dx[nd];
						}

						ny = cny;
						nx = cnx;
					}

					//같은칸에 있는 상어 잡아먹기 
					if (!newshark[ny][nx].empty()) {
						if (newshark[ny][nx][0].size < nz) {
							newshark[ny][nx].pop_back();
							newshark[ny][nx].push_back({ ny, nx, ns, nd, nz });
						}
					}
					else {
						newshark[ny][nx].push_back({ ny, nx, ns, nd, nz });
					}
				}
			}
		}

		//newshark -> shark옮기기 
		for (int i = 1; i <= r; i++) {
			for (int j = 1; j <= c; j++) {
				shark[i][j] = newshark[i][j];
			}
		}
	}

	cout << result << endl;

	return 0;
}