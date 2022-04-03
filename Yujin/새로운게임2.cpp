#include <iostream>
#include <deque>
#include <stack>
using namespace std;

struct hinfo {
	int y;
	int x;
	int d;
};

int n, k;
deque<int> map[13][13];
int color[13][13];
hinfo horse[11];
int dx[5] = { 0,1,-1,0,0 };
int dy[5] = { 0,0,0,-1,1 };

void input() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> color[i][j];
		}
	}
	for (int i = 1; i <= k; i++) {
		int y = 0, x = 0, d = 0;
		cin >> y >> x >> d;
		horse[i] = { y, x, d };
		map[y][x].push_back(i);
	}
}

bool move() {
	for (int i = 1; i <= k; i++) {
		int y = horse[i].y;
		int x = horse[i].x;
		int d = horse[i].d;

		int ny = y + dy[d];
		int nx = x + dx[d];

		//ÆÄ¶ûÀÌ°Å³ª ¹þ¾î³ª´Â °æ¿ì
		if (ny <= 0 || nx <= 0 || nx > n || ny > n || color[ny][nx] == 2) {
			if (d == 1) d = 2;
			else if (d == 2) d = 1;
			else if (d == 3) d = 4;
			else if (d == 4) d = 3;

			horse[i].d = d;
			ny = y + dy[d];
			nx = x + dx[d];

			if (ny <= 0 || nx <= 0 || nx > n || ny > n || color[ny][nx] == 2) continue;
			//Èò»öÀÎ°æ¿ì
			else if (color[ny][nx] == 0) {
				stack<int> tmp;
				while (!map[y][x].empty()) {
					if (map[y][x].back() == i) {
						tmp.push(map[y][x].back());
						map[y][x].pop_back();
						break;
					}
					tmp.push(map[y][x].back());
					map[y][x].pop_back();
				}

				while (!tmp.empty()) {
					horse[tmp.top()].y = ny;
					horse[tmp.top()].x = nx;
					map[ny][nx].push_back(tmp.top());
					tmp.pop();
				}

				//4°³ ÀÌ»ó ½×¿´À¸¸é
				if (map[ny][nx].size() >= 4) return false;
			}
			//»¡°­ÀÎ°æ¿ì
			else if (color[ny][nx] == 1) {
				while (!map[y][x].empty()) {
					if (map[y][x].back() == i) {
						horse[map[y][x].back()].y = ny;
						horse[map[y][x].back()].x = nx;
						map[ny][nx].push_back(map[y][x].back());
						map[y][x].pop_back();
						break;
					}
					horse[map[y][x].back()].y = ny;
					horse[map[y][x].back()].x = nx;
					map[ny][nx].push_back(map[y][x].back());
					map[y][x].pop_back();
				}

				//4°³ ÀÌ»ó ½×¿´À¸¸é
				if (map[ny][nx].size() >= 4) return false;
			}
		}
		//Èò»öÀÎ°æ¿ì
		else if (color[ny][nx] == 0) {
			stack<int> tmp;
			while (!map[y][x].empty()) {
				if (map[y][x].back() == i) {
					tmp.push(map[y][x].back());
					map[y][x].pop_back();
					break;
				}
				tmp.push(map[y][x].back());
				map[y][x].pop_back();
			}

			while (!tmp.empty()) {
				horse[tmp.top()].y = ny;
				horse[tmp.top()].x = nx;
				map[ny][nx].push_back(tmp.top());
				tmp.pop();
			}

			//4°³ ÀÌ»ó ½×¿´À¸¸é
			if (map[ny][nx].size() >= 4) return false;
		}
		//»¡°­ÀÎ°æ¿ì
		else if (color[ny][nx] == 1) {
			while (!map[y][x].empty()) {
				if (map[y][x].back() == i) {
					horse[map[y][x].back()].y = ny;
					horse[map[y][x].back()].x = nx;
					map[ny][nx].push_back(map[y][x].back());
					map[y][x].pop_back();
					break;
				}
				horse[map[y][x].back()].y = ny;
				horse[map[y][x].back()].x = nx;
				map[ny][nx].push_back(map[y][x].back());
				map[y][x].pop_back();
			}

			//4°³ ÀÌ»ó ½×¿´À¸¸é
			if (map[ny][nx].size() >= 4) return false;
		}
	}

	return true;
}
int main() {
	input();
	int turn = 0;
	for (turn = 1; turn <= 1000; turn++) {
		bool check = move();
		if (check == false) break;
	}

	if (turn == 1001) turn = -1;
	cout << turn << "\n";
	return 0;
}