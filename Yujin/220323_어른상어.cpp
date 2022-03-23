#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct smell_info {
	int host;
	int cnt;
};

int dy[5] = { 0,-1,1,0,0 };
int dx[5] = { 0,0,0,-1,1 };

int n, m, k;
int now_dir[401] = { 0, };
int dir[401][5][5];
vector<int> map[21][21]; //»ó¾î ¹øÈ£
smell_info smell[21][21];

void smell_split() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j].size() > 0) {
				int num = map[i][j][0];
				smell[i][j].host = num;
				smell[i][j].cnt = k;
			}
		}
	}
}

void shark_move() {
	//sharkÀÇ ÀÌµ¿ : tmp¿¡ ±â·Ï
	vector<int> tmp[21][21];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j].size() > 0) {
				int num = map[i][j][0];
				int nd = now_dir[num];

				//³¿»õ¾ø´ÂÄ­ Å½»ö
				int flag = 0;
				for (int l = 1; l <= 4; l++) {
					int d = dir[num][nd][l];
					int ny = i + dy[d];
					int nx = j + dx[d];

					if (ny <= 0 || nx <= 0 || ny > n || nx > n) continue;
					if (smell[ny][nx].cnt != 0) continue;
					//³¿»õ¾ø´ÂÄ­ ¹ß°ß
					tmp[ny][nx].push_back(num);
					now_dir[num] = d;
					flag = 1;
					break;
				}
				if (flag == 1) continue;

				//³¿»õ¾ø´ÂÄ­ ¾ø¾î¼­ ÀÚ±âÄ­À¸·Î µ¹¾Æ°¡±â
				for (int l = 1; l <= 4; l++) {
					int d = dir[num][nd][l];
					int ny = i + dy[d];
					int nx = j + dx[d];

					if (ny <= 0 || nx <= 0 || ny > n || nx > n) continue;
					if (smell[ny][nx].host == num) {
						tmp[ny][nx].push_back(num);
						now_dir[num] = d;
						break;
					}
				}
			}
		}
	}

	// map¿¡ º¹»ç
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[i][j] = tmp[i][j];
		}
	}

	//Áö³­Ä­ ³¿»õ -1
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (smell[i][j].cnt != 0) {
				smell[i][j].cnt--;
			}
			if (smell[i][j].cnt == 0) {
				smell[i][j].host = 0;
			}
		}
	}
}

void remove_shark() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j].empty()) continue;
			sort(map[i][j].begin(), map[i][j].end());
			int live = map[i][j][0];
			map[i][j].clear();
			map[i][j].push_back(live);
		}
	}
}

bool check() {
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!map[i][j].empty()) cnt++;
		}
	}

	if (cnt == 1) return true;
	else return false;
}

void input() {
	cin >> n >> m >> k;
	//nÄ­¼ö, m»ó¾î¼ö, k³¿»õÀÜ·ù½Ã°£
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int x = 0;
			cin >> x;
			if (x != 0) map[i][j].push_back(x);
		}
	}
	for (int i = 1; i <= m; i++) {
		int d = 0;
		cin >> d;
		now_dir[i] = d;
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int l = 1; l <= 4; l++) {
				cin >> dir[i][j][l];
			}
		}
	}
}

int main() {
	input();

	int turn = 0;
	smell_split();

	while (1) {
		if (turn == 1000) {
			turn = -1;
			break;
		}
		shark_move();

		remove_shark();

		smell_split();
		turn++;

		if (check()) {
			break;
		}
	}

	cout << turn << "\n";

	return 0;
}