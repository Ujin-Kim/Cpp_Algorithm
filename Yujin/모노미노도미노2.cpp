#include <iostream>
#include <vector>
using namespace std;

struct node {
	int t;
	int x;
	int y;
};
int n;
int green[6][4];
int blue[4][6];
int score;
vector<node> v;

void stack_block(int t, int x, int y) {
	if (t == 1) {
		int flag = 0;
		for (int i = 0; i <= 5; i++) {
			if (green[i][y] == 1) {
				green[i - 1][y] = 1;
				flag = 1;
				break;
			}
		}
		if (flag == 0) green[5][y] = 1;

		flag = 0;
		for (int i = 0; i <= 5; i++) {
			if (blue[x][i] == 1) {
				blue[x][i-1] = 1;
				flag = 1;
				break;
			}
		}
		if (flag == 0) blue[x][5] = 1;
	}
	else if (t == 2) {
		int flag = 0;
		for (int i = 0; i <= 5; i++) {
			if (green[i][y] == 1 || green[i][y+1] == 1) {
				green[i - 1][y] = 1;
				green[i - 1][y + 1] = 1;
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			green[5][y] = 1;
			green[5][y + 1] = 1;
		}

		flag = 0;
		for (int i = 0; i <= 5; i++) {
			if (blue[x][i] == 1) {
				blue[x][i - 1] = 1;
				blue[x][i - 2] = 1;
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			blue[x][5] = 1;
			blue[x][4] = 1;
		}
	}
	else if (t == 3) {
		int flag = 0;
		for (int i = 0; i <= 5; i++) {
			if (green[i][y] == 1) {
				green[i - 1][y] = 1;
				green[i - 2][y] = 1;
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			green[5][y] = 1;
			green[4][y] = 1;
		}

		flag = 0;
		for (int i = 0; i <= 5; i++) {
			if (blue[x][i] == 1 || blue[x+1][i] == 1) {
				blue[x][i - 1] = 1;
				blue[x + 1][i - 1] = 1;
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			blue[x][5] = 1;
			blue[x + 1][5] = 1;
		}
	}
}

void remove_line() {
	//green
	for (int i = 0; i <= 5; i++) {
		int flag = 0;
		for (int j = 0; j < 4; j++) {
			if (green[i][j] == 0) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			for (int j = 0; j < 4; j++) {
				green[i][j] = 0;
			}
			score++;
		}
	}

	//blue
	for (int i = 0; i <= 5; i++) {
		int flag = 0;
		for (int j = 0; j < 4; j++) {
			if (blue[j][i] == 0) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			for (int j = 0; j < 4; j++) {
				blue[j][i] = 0;
			}
			score++;
		}
	}
}

void gravity() {
	//green
	for (int i = 5; i > 0; i--) {
		int flag = 0;
		for (int j = 0; j < 4; j++) {
			if (green[i][j] == 1) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			for (int j = 0; j < 4; j++) {
				green[i][j] = green[i-1][j];
				green[i - 1][j] = 0;
			}
		}
	}

	//blue
	for (int i = 5; i > 0; i--) {
		int flag = 0;
		for (int j = 0; j < 4; j++) { //비어있지않음 1
			if (blue[j][i] == 1) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) { //비어있으면 0
			for (int j = 0; j < 4; j++) {
				blue[j][i] = blue[j][i-1];
				blue[j][i-1] = 0;
			}
		}
	}
}

void lightmap() {
	int flag = 1;
	while (flag) {
		flag = 0;
		for (int j = 0; j < 4; j++) {
			if (green[1][j] == 1) { //연한칸에 블럭이 있다
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			for (int j = 0; j < 4; j++) {
				green[5][j] = 0;
			}
		}

		gravity();
	}
	
	flag = 1;
	while (flag) {
		flag = 0;
		for (int j = 0; j < 4; j++) {
			if (blue[j][1] == 1) { //연한칸에 블럭이 있다
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			for (int j = 0; j < 4; j++) {
				blue[j][5] = 0;
			}
		}
		gravity();
	}
}

int main() {

	cin >> n;
	for (int i = 0; i < n; i++) {
		int t = 0, x = 0, y = 0;
		cin >> t >> x >> y;
		v.push_back({ t, x, y });
	}

	//시작
	for (int i = 0; i < n; i++) {
		int type = v[i].t;
		int x = v[i].x;
		int y = v[i].y;

		stack_block(type, x, y);
		remove_line();
		gravity();
		lightmap();
	}

	int blockcnt = 0;
	for (int i = 0; i <= 5; i++) {
		for (int j = 0; j < 4; j++) {
			if (green[i][j] == 1) blockcnt++;
			if (blue[j][i] == 1) blockcnt++;
		}
	}
	cout << score << "\n";
	cout << blockcnt << "\n";
	return 0;
}