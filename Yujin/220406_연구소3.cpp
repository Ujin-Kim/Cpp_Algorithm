#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct info {
	int y;
	int x;
};

int n, m; //�������� ũ��, ���̷����� ���� 
int map[51][51]; //0��ĭ, 1��, 2���̷���
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
			//���϶� 
			if (map[ny][nx] == 1) continue;
			//��Ȱ��ȭ ���̷����� ������ �ʰ�, ��ĭ�� ���� 
			if (sec[ny][nx] == -1) {
				//�ð� ++ 
				sec[ny][nx] = sec[y][x] + 1;
				q.push({ ny, nx });
			}
		}
	}

	//������� �ִ��� check
	bool check = true;
	int maxtime = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 0) { //ó���� ��ĭ�̾��� 
				if (sec[i][j] == -1) { //���̷����� ���������� 
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
		//q�� ������ virus �ֱ� 
		for (int i = 0; i < m; i++) {
			q.push({ s_virus[i].y, s_virus[i].x });
		}

		//sec�迭 �ʱ�ȭ
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				sec[i][j] = -1;
			}
		}

		//���õ� virus�� sec�� 0���� ����
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
	//m�� ����
	selection(0, 0);

	if (result == 987654321) result = -1;
	cout << result << "\n";

	return 0;
}