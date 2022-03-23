#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct info {
	int sy;
	int sx;
	int ey;
	int ex;
};

struct node {
	int y;
	int x;
	int cnt;
};

int N, M, fuel;
int map[21][21];
int dy[5] = { 0,0,0,-1,1 };
int dx[5] = { 0,1,-1,0,0 };
int tx_x, tx_y;
vector<info> cust;

//cnt, y, x �� ���� ������ ����
bool cmp(node front, node back) {
	if (front.cnt == back.cnt) {
		if (front.y == back.y) {
			return front.x < back.x;
		}
		return front.y < back.y;
	}
	return front.cnt < back.cnt;
}

int find_cust() {
	int visited[21][21] = { 0, };
	queue<node> q;
	vector<node> near;
	q.push({ tx_y, tx_x, 0 });
	visited[tx_y][tx_x] = 0; //���ڸ��� �ѹ� �� �˻��� �� �ֵ��� �̸� �湮 ǥ�ø� ���� �ʴ´�.

	while (!q.empty()) {
		int y = q.front().y;
		int x = q.front().x;
		int c = q.front().cnt;
		q.pop();

		for (int i = 0; i < 5; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny <= 0 || nx <= 0 || ny > N || nx > N) continue;
			if (map[ny][nx] == 1) continue;
			if (visited[ny][nx] == 1) continue;
			visited[ny][nx] = 1;
			if (i == 0) q.push({ ny, nx, c }); //���ڸ� �˻��� ���� �Ÿ��� �� �´�.
			else q.push({ ny, nx, c + 1 });
			if (map[ny][nx] == 2 && i == 0) near.push_back({ ny, nx, c });
			else if (map[ny][nx] == 2 && i != 0) near.push_back({ ny, nx, c + 1 });
		}
	}

	//bfs�� �Ϸ�� �Ŀ�, �մ��� �����Ѵ�.
	if (near.size() > 0) {
		sort(near.begin(), near.end(), cmp);
		tx_y = near[0].y; //�մ� ��ġ�� �ý� �̵���Ű��
		tx_x = near[0].x;
		fuel -= near[0].cnt;
		if (fuel <= 0) return -1;
		map[tx_y][tx_x] = 0; //�մ� ������ٰ� üũ
		return 0;
	}

	return -1;
}

int bfs(int sy, int sx, int ey, int ex) {
	int visited[21][21] = { 0, };
	queue<node> q;
	q.push({ sy, sx, 0 });
	visited[sy][sx] = 0;

	while (!q.empty()) {
		int y = q.front().y;
		int x = q.front().x;
		int c = q.front().cnt;
		q.pop();

		if (y == ey && x == ex) {
			tx_y = y;
			tx_x = x;

			fuel -= c; // �մ��¿�� �̵�
			if (fuel < 0) return -1;
			else {
				fuel += c * 2; //�մ� �¿�� �̵��� ��ŭ�� *2
				return 0;
			}
		}

		for (int i = 0; i < 5; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny <= 0 || nx <= 0 || ny > N || nx > N) continue;
			if (map[ny][nx] == 1) continue;
			if (visited[ny][nx] == 1) continue;
			visited[ny][nx] = 1;
			if (i == 0) q.push({ ny, nx, c });
			else q.push({ ny, nx, c + 1 });
		}
	}

	return -1;
}

int dest() {
	for (int i = 0; i < cust.size(); i++) {
		if (cust[i].sy == tx_y && cust[i].sx == tx_x) {
			int is_success = bfs(tx_y, tx_x, cust[i].ey, cust[i].ex);
			return is_success;
		}
	}
}

int main() {
	//input
	cin >> N >> M >> fuel;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}
	cin >> tx_y >> tx_x;
	for (int i = 0; i < M; i++) {
		int sy = 0, sx = 0, ey = 0, ex = 0;
		cin >> sy >> sx >> ey >> ex;
		map[sy][sx] = 2;
		cust.push_back({ sy, sx, ey, ex });
	}

	//start
	for (int m = 0; m < M; m++) {
		int is_suc = 0;
		is_suc = find_cust();
		if (is_suc == -1) {
			cout << is_suc << "\n";
			return 0;
		}
		is_suc = dest();
		if (is_suc == -1) {
			cout << is_suc << "\n";
			return 0;
		}
	}
	cout << fuel << "\n";

	return 0;
}