#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

struct info {
	int d;
	int s;
};
int n, m;
int res[4];
int map[50][50];
int dx[5] = { 0,0,0,-1,1 };
int dy[5] = { 0,-1,1,0,0 };
vector<info> magic;

void start_magic(int d, int s) {
	int sy = (n + 1) / 2;
	int sx = (n + 1) / 2;

	for (int i = 1; i <= s; i++) {
		sy += dy[d];
		sx += dx[d];
		map[sy][sx] = 0;
	}
}

int move_bomb_change() {
	int sy = (n + 1) / 2;
	int sx = (n + 1) / 2;
	vector<int> line;

	//map -> line
	for (int i = 1; i < n; i++) {
		if (i % 2 == 1) {
			for (int j = 0; j < i; j++) { //좌
				sy += dy[3];
				sx += dx[3];
				if(map[sy][sx] != 0) line.push_back(map[sy][sx]);
			}
			for (int j = 0; j < i; j++) { //하
				sy += dy[2];
				sx += dx[2];
				if (map[sy][sx] != 0) line.push_back(map[sy][sx]);
			}
		}
		else {
			for (int j = 0; j < i; j++) { //우
				sy += dy[4];
				sx += dx[4];
				if (map[sy][sx] != 0) line.push_back(map[sy][sx]);
			}
			for (int j = 0; j < i; j++) { //상
				sy += dy[1];
				sx += dx[1];
				if (map[sy][sx] != 0) line.push_back(map[sy][sx]);
			}
		}
		if (i == n - 1) {
			for (int j = 0; j < i; j++) { //좌
				sy += dy[3];
				sx += dx[3];
				if (map[sy][sx] != 0) line.push_back(map[sy][sx]);
			}
		}
	}
	memset(map, 0, sizeof(map));
	
	int ball = 0, cnt = 0, bomb = -1;
	while (1) {
		if (line.empty()) return -1;
		if (bomb == 0) break;
		ball = 0, cnt = 0, bomb = 0;
		//연속하는 구슬 폭발
		vector<int> line2;
		for (int i = 0; i < line.size(); i++) {
			if (ball != line[i] && cnt >= 4) { //4개 이상인 경우
				res[ball] += cnt;
				bomb++;
				ball = line[i];
				cnt = 1;
			}
			else if (ball != line[i] && cnt < 4) {
				for (int j = 0; j < cnt; j++) line2.push_back(ball);
				ball = line[i];
				cnt = 1;
			}
			else if (ball == line[i]) cnt++;
			if (i == line.size() - 1 && cnt >= 4) {
				res[ball] += cnt;
			}
			else if(i == line.size() -1 && cnt < 4) {
				for (int j = 0; j < cnt; j++) line2.push_back(ball);
			}
		}
		line = line2;
	}
	//구슬 변화
	vector<int> line2;
	int ball_cnt = 1, ball_num = line[0];
	for (int i = 1; i < line.size(); i++) {
		if (ball_num != line[i]) {
			line2.push_back(ball_cnt);
			line2.push_back(ball_num);
			ball_cnt = 1;
			ball_num = line[i];
		}
		else ball_cnt++;
		if (i == line.size() - 1) {
			line2.push_back(ball_cnt);
			line2.push_back(ball_num);
		}
	}

	//line2 -> map
	if (line2.empty()) return -1;
	cnt = 0;
	sy = (n + 1) / 2;
	sx = (n + 1) / 2;
	for (int i = 1; i < n; i++) {

		if (i % 2 == 1) {
			for (int j = 0; j < i; j++) { //좌
				sy += dy[3];
				sx += dx[3];
				if (line2.size() > cnt) map[sy][sx] = line2[cnt], cnt++;
			}
			for (int j = 0; j < i; j++) { //하
				sy += dy[2];
				sx += dx[2];
				if (line2.size() > cnt) map[sy][sx] = line2[cnt], cnt++;
			}
		}
		else {
			for (int j = 0; j < i; j++) { //우
				sy += dy[4];
				sx += dx[4];
				if (line2.size() > cnt) map[sy][sx] = line2[cnt], cnt++;
			}
			for (int j = 0; j < i; j++) { //상
				sy += dy[1];
				sx += dx[1];
				if (line2.size() > cnt) map[sy][sx] = line2[cnt], cnt++;
			}
		}
		if (i == n - 1) {
			for (int j = 0; j < i; j++) { //좌
				sy += dy[3];
				sx += dx[3];
				if (line2.size() > cnt) map[sy][sx] = line2[cnt], cnt++;
			}
		}
		if (line2.size() == cnt) break;
	}
	return 0;
}

int main() {

	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < m; i++) {
		int d = 0, s = 0;
		cin >> d >> s;
		magic.push_back({ d, s });
	}

	for (int t = 0; t < m; t++) {
		int d = magic[t].d;
		int s = magic[t].s;

		start_magic(d, s);
		if (move_bomb_change() == -1) break;
	}

	int answer = 0;
	for (int i = 1; i <= 3; i++) {
		answer += i * res[i];
	}
	cout << answer << "\n";
	return 0;
}