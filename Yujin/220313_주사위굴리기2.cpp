#include <iostream>
#include <string.h>
using namespace std;

int n, m, k;
int res;
int cnt;
int dice_x, dice_y;
int dice_dir; //0동, 1서, 2남, 3북
int map[21][21];
int visited[21][21];
int dice[4][3] = {
	{0,2,0},
	{4,1,3},
	{0,5,0},
	{0,6,0}
};
int dx[4] = {0,0,1,-1}; //우, 좌, 하, 상
int dy[4] = {1,-1,0,0};

void rotate_dice(int dice_dir) {
	if (dice_dir == 0) { //동
		int temp = dice[1][2];
		dice[1][2] = dice[1][1];
		dice[1][1] = dice[1][0];
		dice[1][0] = dice[3][1];
		dice[3][1] = temp;
 	}
	else if (dice_dir == 1) { //서
		int temp = dice[1][0];
		dice[1][0] = dice[1][1];
		dice[1][1] = dice[1][2];
		dice[1][2] = dice[3][1];
		dice[3][1] = temp;
	}
	else if (dice_dir == 2) { //남
		int temp = dice[3][1];
		dice[3][1] = dice[2][1];
		dice[2][1] = dice[1][1];
		dice[1][1] = dice[0][1];
		dice[0][1] = temp;
	}
	else if (dice_dir == 3) { //북
		int temp = dice[0][1];
		dice[0][1] = dice[1][1];
		dice[1][1] = dice[2][1];
		dice[2][1] = dice[3][1];
		dice[3][1] = temp;
	}
}

void move_dice() {
	int nx = dice_x + dx[dice_dir];
	int ny = dice_y + dy[dice_dir];

	//경계넘으면 이동방향 반대로
	if (1 > nx || 1 > ny || n < nx || m < ny) {
		if (dice_dir == 0) dice_dir = 1;
		else if (dice_dir == 1) dice_dir = 0;
		else if (dice_dir == 2) dice_dir = 3;
		else dice_dir = 2;
	}

	dice_x = dice_x + dx[dice_dir];
	dice_y = dice_y + dy[dice_dir];

	rotate_dice(dice_dir);
}

void dfs(int x, int y, int tar) {
	if (map[x][y] == tar) {
		cnt++;
	}
	if (map[x][y] != tar) return;

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (1 > nx || 1 > ny || n < nx || m < ny) continue;
		if (visited[nx][ny] == 1) continue;
		visited[nx][ny] = 1;
		dfs(nx, ny, tar);
	}
}

void get_score() {
	int b = map[dice_x][dice_y];
	memset(visited, 0, sizeof(visited));
	cnt = 0;
	visited[dice_x][dice_y] = 1;
	dfs(dice_x, dice_y, b);

	res += cnt * b;
}

void set_dir() {
	int a = dice[3][1];
	int b = map[dice_x][dice_y];

	if (a > b) {
		if (dice_dir == 0) dice_dir = 2;
		else if (dice_dir == 1) dice_dir = 3;
		else if (dice_dir == 2) dice_dir = 1;
		else dice_dir = 0;
	}
	else if (a < b) {
		if (dice_dir == 0) dice_dir = 3;
		else if (dice_dir == 1) dice_dir = 2;
		else if (dice_dir == 2) dice_dir = 0;
		else dice_dir = 1;
	}
}

int main() {

	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> map[i][j];
		}
	}
	dice_x = 1, dice_y = 1;
	dice_dir = 0;
	for (int i = 1; i <= k; i++) {
		move_dice();
		get_score();
		set_dir();
	}

	cout << res << "\n";
	return 0;
}