#include <iostream>
#include <vector>
using namespace std;

int n;
int res;
int map[21][21];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
vector<int> order;
vector<int> fav[401];

void find_seat(int tar) {
	int num = order[tar];

	int ty = n+1, tx = n+1;
	int favorite = 0;
	int empty = 0;

	//map을 전체 순회
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int temp_fav = 0;
			int temp_empty = 0;
			//자리가 아직 안채워졌으면
			if (map[i][j] == 0) {
				//인접칸에 뭐가 있나 확인
				for (int k = 0; k < 4; k++) {
					int ny = i + dy[k];
					int nx = j + dx[k];
					//경계를 넘지않으면
					if (1 <= ny && ny <= n && 1 <= nx && nx <= n) {
						if (map[ny][nx] == 0) temp_empty++;
						else {
							for (int l = 0; l < fav[num].size(); l++) {
								if (fav[num][l] == map[ny][nx]) {
									temp_fav++;
									break;
								}
							}
						}
					}
				}
				if (favorite < temp_fav) ty = i, tx = j, favorite = temp_fav, empty = temp_empty;
				else if (favorite == temp_fav && empty < temp_empty) ty = i, tx = j, empty = temp_empty;
				else if (favorite == temp_fav && empty == temp_empty && ty > i) ty = i, tx = j;
				else if(favorite == temp_fav && empty == temp_empty && ty == i && tx > j) ty = i, tx = j;
			}
		}
	}

	map[ty][tx] = num;
}

int main() {

	cin >> n;
	for (int i = 0; i < n * n; i++) {
		int num = 0, f1 = 0, f2 = 0, f3 = 0, f4 = 0;
		cin >> num >> f1 >> f2 >> f3 >> f4;
		order.push_back(num);
		fav[num] = {f1, f2, f3, f4};
	}

	for (int i = 0; i < order.size(); i++) {
		find_seat(i);
	}

	//결과
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];
				//경계를 넘지않으면
				if (1 <= ny && ny <= n && 1 <= nx && nx <= n) {
					for (int l = 0; l < fav[map[i][j]].size(); l++) {
						if (fav[map[i][j]][l] == map[ny][nx]) {
							cnt++;
							break;
						}
					}
				}
			}
			if (cnt == 1) res += 1;
			else if (cnt == 2) res += 10;
			else if (cnt == 3) res += 100;
			else if (cnt == 4) res += 1000;
		}
	}

	cout << res;
	return 0;
}