#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

struct info {
	int x;
	int y;
	int dir;
};
int r, c, k, w;
int map[22][22];
int wall[25][25][2];
int temp[22][22];
int dx[5] = { 0,0,0,-1,1 }; // x,��,��,��,��
int dy[5] = { 0,1,-1,0,0 };
vector<info> heater;

void wind() {
	for (int i = 0; i < heater.size(); i++) {
		int x = heater[i].x;
		int y = heater[i].y;
		int dir = heater[i].dir;

		int visited[22][22] = { 0, };

		//������ ����������
		if (dir == 1) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			temp[nx][ny] += 5;
			visited[nx][ny] = 1;
			queue<info> q;
			q.push({ nx, ny, 5 });
			while (!q.empty()) {
				int tx = q.front().x;
				int ty = q.front().y;
				int t = q.front().dir;
				q.pop();

				if (t == 1) break;

				//�밢�� ��
				if (1 <= tx - 1 && tx - 1 <= r && 1 <= ty + 1 && ty + 1 <= c) {
					if (visited[tx - 1][ty + 1] != 1) {
						if (wall[tx][ty][0] != 1 && wall[tx - 1][ty][1] != 1) {
							visited[tx - 1][ty + 1] = 1;
							temp[tx - 1][ty + 1] += (t - 1);
							q.push({ tx - 1, ty + 1, t - 1 });
						}
					}
				}
				//������
				if (1 <= tx && tx <= r && 1 <= ty + 1 && ty + 1 <= c) {
					if (visited[tx][ty + 1] != 1) {
						if (wall[tx][ty][1] != 1) {
							visited[tx][ty + 1] = 1;
							temp[tx][ty + 1] += (t - 1);
							q.push({ tx, ty + 1, t - 1 });
						}
					}
				}
				//�밢���Ʒ�
				if (1 <= tx + 1 && tx + 1 <= r && 1 <= ty + 1 && ty + 1 <= c) {
					if (visited[tx + 1][ty + 1] != 1) {
						if (wall[tx + 1][ty][0] != 1 && wall[tx + 1][ty][1] != 1){
							visited[tx + 1][ty + 1] = 1;
							temp[tx + 1][ty + 1] += (t - 1);
							q.push({ tx + 1, ty + 1, t - 1 });
						}
					}
				}
			}
		}
		//����
		else if (dir == 2) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			temp[nx][ny] += 5;
			visited[nx][ny] = 1;
			queue<info> q;
			q.push({ nx, ny, 5 });
			while (!q.empty()) {
				int tx = q.front().x;
				int ty = q.front().y;
				int t = q.front().dir;
				q.pop();

				if (t == 1) break;

				//�밢�� ��
				if (1 <= tx - 1 && tx - 1 <= r && 1 <= ty - 1 && ty - 1 <= c) {
					if (visited[tx - 1][ty - 1] != 1) {
						if (wall[tx][ty][0] != 1 && wall[tx - 1][ty-1][1] != 1) {
							visited[tx - 1][ty - 1] = 1;
							temp[tx - 1][ty - 1] += (t - 1);
							q.push({ tx - 1, ty - 1, t - 1 });
						}
					}
				}
				//����
				if (1 <= tx && tx <= r && 1 <= ty - 1 && ty - 1 <= c) {
					if (visited[tx][ty - 1] != 1) {
						if (wall[tx][ty-1][1] != 1) {
							visited[tx][ty - 1] = 1;
							temp[tx][ty - 1] += (t - 1);
							q.push({ tx, ty - 1, t - 1 });
						}
					}
				}
				//�밢�� �Ʒ�
				if (1 <= tx + 1 && tx + 1 <= r && 1 <= ty - 1 && ty - 1 <= c) {
					if (visited[tx + 1][ty - 1] != 1) {
						if (wall[tx + 1][ty][0] != 1 && wall[tx + 1][ty-1][1] != 1) {
							visited[tx + 1][ty - 1] = 1;
							temp[tx + 1][ty - 1] += (t - 1);
							q.push({ tx + 1, ty - 1, t - 1 });
						}
					}
				}
			}
		}
		//����
		else if (dir == 3) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			temp[nx][ny] += 5;
			visited[nx][ny] = 1;
			queue<info> q;
			q.push({ nx, ny, 5 });
			while (!q.empty()) {
				int tx = q.front().x;
				int ty = q.front().y;
				int t = q.front().dir;
				q.pop();

				if (t == 1) break;

				//�밢�� ��
				if (1 <= tx - 1 && tx - 1 <= r && 1 <= ty - 1 && ty - 1 <= c) {
					if (visited[tx - 1][ty - 1] != 1) {
						if (wall[tx][ty-1][1] != 1 && wall[tx][ty - 1][0] != 1) {
							visited[tx - 1][ty - 1] = 1;
							temp[tx - 1][ty - 1] += (t - 1);
							q.push({ tx - 1, ty - 1, t - 1 });
						}
					}
				}
				//��
				if (1 <= tx -1 && tx-1 <= r && 1 <= ty && ty <= c) {
					if (visited[tx-1][ty] != 1) {
						if (wall[tx][ty][0] != 1) {
							visited[tx-1][ty] = 1;
							temp[tx-1][ty] += (t - 1);
							q.push({ tx-1, ty, t - 1 });
						}
					}
				}
				//�밢�� ��
				if (1 <= tx -1 && tx - 1 <= r && 1 <= ty + 1 && ty + 1 <= c) {
					if (visited[tx - 1][ty + 1] != 1) {
						if (wall[tx][ty+1][0] != 1 && wall[tx][ty][1] != 1) {
							visited[tx - 1][ty + 1] = 1;
							temp[tx - 1][ty + 1] += (t - 1);
							q.push({ tx - 1, ty + 1, t - 1 });
						}
					}
				}
			}
		}
		//�Ʒ���
		else if (dir == 4) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			temp[nx][ny] += 5;
			visited[nx][ny] = 1;
			queue<info> q;
			q.push({ nx, ny, 5 });
			while (!q.empty()) {
				int tx = q.front().x;
				int ty = q.front().y;
				int t = q.front().dir;
				q.pop();
				if (t == 1) break;
				//���ȳѰ�
				if (1 <= tx + 1 && tx + 1 <= r && 1 <= ty - 1 && ty - 1 <= c) {
					//���� ��ǳ�Ⱑ ��������
					if (visited[tx + 1][ty - 1] != 1) {
						//���±��� �ȸ���������
						if (wall[tx+1][ty-1][0] != 1 && wall[tx][ty-1][1] != 1) {
							visited[tx + 1][ty - 1] = 1;
							temp[tx + 1][ty - 1] += (t - 1);
							q.push({ tx + 1, ty - 1, t - 1 });
						}
					}
				}
				if (1 <= tx+1 && tx+1 <= r && 1 <= ty && ty <= c) {
					if (visited[tx+1][ty] != 1) {
						if (wall[tx+1][ty][0] != 1) {
							visited[tx+1][ty] = 1;
							temp[tx+1][ty] += (t - 1);
							q.push({ tx+1, ty, t - 1 });
						}
					}
				}
				if (1 <= tx + 1 && tx + 1 <= r && 1 <= ty + 1 && ty + 1 <= c) {
					if (visited[tx + 1][ty + 1] != 1) {
						if (wall[tx + 1][ty+1][0] != 1 && wall[tx][ty][1] != 1) {
							visited[tx + 1][ty + 1] = 1;
							temp[tx + 1][ty + 1] += (t - 1);
							q.push({ tx + 1, ty + 1, t - 1 });
						}
					}
				}
			}
		}
	}
}

void control_temp() {
	int visited[25][25] = { 0, };
	int temp2[25][25] = { 0, };
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			temp2[i][j] = temp[i][j];
		}
	}
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			visited[i][j] = 1;
			for (int l = 1; l <= 4; l++) {
				int nx = i + dx[l];
				int ny = j + dy[l];
				//��踦 �����ʰ�
				if (1 <= nx && nx <= r && 1 <= ny && ny <= c){
					//�� ĭ ���̿� ���� ����
					if (l == 1 && wall[i][j][1] == 1) continue;
					if (l == 2 && wall[i][j - 1][1] == 1) continue;
					if (l == 3 && wall[i][j][0] == 1) continue;
					if (l == 4 && wall[i + 1][j][0] == 1) continue;
					//���� ������ �ʾ��� ��
					if (visited[nx][ny] == 1) continue;
					
					int ab = abs(temp[i][j] - temp[nx][ny]) / 4;
					if (temp[i][j] > temp[nx][ny]) {
						temp2[i][j] -= ab;
						temp2[nx][ny] += ab;
					}
					else {
						temp2[i][j] += ab;
						temp2[nx][ny] -= ab;
					}
				}
			}
		}
	}
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			temp[i][j] = temp2[i][j];
		}
	}
}

void outside_temp() {
	for (int i = 1; i <= r; i++) {
		if (temp[i][1] > 0) temp[i][1] -= 1;
		if (temp[i][c] > 0) temp[i][c] -= 1;
	}
	for (int j = 2; j <= c - 1; j++) {
		if (temp[1][j] > 0) temp[1][j] -= 1;
		if (temp[r][j] > 0) temp[r][j] -= 1;
	}
}

bool check() {
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			if (map[i][j] == 5 && temp[i][j] < k) return false;
		}
	}
	return true;
}

int main() {
	cin >> r >> c >> k;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			cin >> map[i][j];
			if (1 <= map[i][j] && map[i][j] <= 4) heater.push_back({ i, j, map[i][j] });
		}
	}
	cin >> w;
	for (int i = 0; i < w; i++) {
		int x = 0, y = 0, t = 0;
		cin >> x >> y >> t;
		if (t == 0) wall[x][y][0] = 1;
		else if (t == 1) wall[x][y][1] = 1;
	}

	int eat_choco = 0;
	while (1) {
		// 1. ��� ��ǳ�⿡�� �ٶ� 1��
		wind();
		// 2. �µ�����
		control_temp();
		// 3. �µ� 1 �̻��� ���� �ٱ� �µ� -1
		outside_temp();
		// 4. ���ݸ��Ա�
		eat_choco += 1;
		// 5. �����ϴ� ĭ �µ� K �̻����� �˻�
		if (check()) break;
		//�Դ� ���ݸ����� 100 �ʰ��� 101 ���
		if (eat_choco > 100) break;
	}
	cout << eat_choco;
	return 0;
}
