#include <iostream>
#include <vector>
using namespace std;

int n;
int m;
int map[51][51]; // 0: ��ĭ, 1: ��, 2: ġŲ��

vector< pair<int, int> > hs;
vector<pair<int, int> > ck;

int path[15]; // ������ ġŲ������ ����� �迭

int res = 21e8;

void DFS(int lv, int ck_cnt) {

	if (lv == m) { //m���� ġŲ�� ���õǸ�, ������ ġŲ�Ÿ��� ���Ѵ�
		int city_dis = 0;

		for (int i = 0; i < hs.size(); i++) {
			int dis = 21e8;

			for (int j = 0; j < m; j++) {
				int tmp_dis = abs(hs[i].first - ck[path[j]].first) + abs(hs[i].second - ck[path[j]].second);
				if (tmp_dis < dis) dis = tmp_dis;
			}

			// ������ ġŲ�Ÿ�
			city_dis += dis;
		}

		if (city_dis < res) res = city_dis;

		return;
	}

	// m���� ġŲ�� �̱�
	for (int i = ck_cnt; i < ck.size(); i++) {
		path[lv] = i;
		DFS(lv + 1, i + 1);
		path[lv] = 0;
	}

}

int main() {

	cin >> n >> m;

	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			cin >> map[y][x];

			if (map[y][x] == 1) hs.push_back(make_pair(y, x));
			else if (map[y][x] == 2) ck.push_back(make_pair(y, x));
		}
	}

	// m���� ġŲ���� ���� ��, ������ ġŲ�Ÿ� �� �� �ּҰ�
	DFS(0, 0);

	cout << res;

	return 0;
}