#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int r, c, k, result;
int n = 3, m = 3;
int A[101][101];

int main() {
	cin >> r >> c >> k;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> A[i][j];
		}
	}

	while (1) {
		if (result > 100) {
			result = -1;
			break;
		}
		if (A[r - 1][c - 1] == k) {
			break;
		}


		if (n >= m) { //R연산 
			for (int i = 0; i < n; i++) {
				int cnt[101] = { 0, };
				for (int j = 0; j < m; j++) {
					if (A[i][j]) {
						cnt[A[i][j]]++;
						A[i][j] = 0;
					}
				}
				vector<pair<int, int> > v;
				for (int j = 0; j < 101; j++) {
					if (cnt[j]) v.push_back({ cnt[j], j }); //등장횟수, 수 
				}
				sort(v.begin(), v.end()); //first에 맞춰서 sort
				int v_size = v.size();
				m = max(m, v_size * 2);
				for (int j = 0; j < (v_size * 2); j++) {
					if (j % 2 == 0) A[i][j] = v[j / 2].second;
					else A[i][j] = v[j / 2].first;
				}
			}
		}
		else { //C연산 
			for (int i = 0; i < m; i++) {
				int cnt[101] = { 0, };
				for (int j = 0; j < n; j++) {
					if (A[j][i]) {
						cnt[A[j][i]]++;
						A[j][i] = 0;
					}
				}
				vector<pair<int, int> > v;
				for (int j = 0; j < 101; j++) {
					if (cnt[j]) v.push_back({ cnt[j], j }); //등장횟수, 수 
				}
				sort(v.begin(), v.end()); //first에 맞춰서 sort
				int v_size = v.size();
				n = max(n, v_size * 2);
				for (int j = 0; j < (v_size * 2); j++) {
					if (j % 2 == 0) A[j][i] = v[j / 2].second;
					else A[j][i] = v[j / 2].first;
				}
			}
		}

		result++;
	}

	cout << result << endl;
	return 0;
}