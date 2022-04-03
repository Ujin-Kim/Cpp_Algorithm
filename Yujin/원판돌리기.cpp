#include <iostream>
#include <vector>
using namespace std;

struct info {
	int x;
	int d;
	int k;
};
int n, m, t;
int board[51][51];
vector<info> v;

void rotation(int x, int d, int k) {
	for (int i = x; i <= n; i = i + x) { //x의 배수인 원판을
		for(int z = 0; z < k; z++){ //k번
			if (d == 0) { //시계방향으로
				int temp = board[i][m];
				for (int j = m; j > 1; j--) {
					board[i][j] = board[i][j - 1];
				}
				board[i][1] = temp;
			}
			else { //반시계방향으로
				int temp = board[i][1];
				for (int j = 1; j < m; j++) {
					board[i][j] = board[i][j + 1];
				}
				board[i][m] = temp;
			}
		}
	}
}

void find_same() {
	int flag = 0;
	int check[51][51] = { 0, };
	//같은원판
	for (int i = 1; i <= n; i++) {
		for (int j = 2; j <= m; j++) {
			if (board[i][j - 1] == board[i][j] && board[i][j] != 0) {
				check[i][j - 1] = 1;
				check[i][j] = 1;
			}
		}
		if (board[i][1] == board[i][m] && board[i][1] != 0) {
			check[i][1] = 1;
			check[i][m] = 1;
		}
	}
	//인접한
	for (int i = 1; i <= m; i++) {
		for (int j = 2; j <= n; j++) {
			if (board[j-1][i] == board[j][i] && board[j][i] != 0) {
				check[j-1][i] = 1;
				check[j][i] = 1;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (check[i][j] == 1) { //인접한게있으면
				flag = 1;
				board[i][j] = 0;
			}
		}
	}

	if (flag == 0) { // 인접한게 없으면
		int cnt = 0;
		int sum = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (board[i][j] != 0) {
					cnt++;
					sum += board[i][j];
				}
			}
		}
		if (cnt != 0) {
			int s = sum / cnt;
			int nam = sum % cnt;
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= m; j++) {
					if (nam == 0) {
						if (board[i][j] > s) {
							board[i][j] -= 1;
						}
						else if (board[i][j] < s && board[i][j] != 0) {
							board[i][j] += 1;
						}
					}
					else {
						if (board[i][j] > s) {
							board[i][j] -= 1;
						}
						else if (board[i][j] <= s && board[i][j] != 0) {
							board[i][j] += 1;
						}
					}

				}
			}
		}
		
	}
}

int main() {
	cin >> n >> m >> t;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> board[i][j];
		}
	}
	for (int i = 0; i < t; i++) {
		int x = 0, d = 0, k = 0;
		cin >> x >> d >> k;
		v.push_back({ x, d, k });
	}

	for (int turn = 0; turn < t; turn++) {
		int x = v[turn].x;
		int d = v[turn].d;
		int k = v[turn].k;

		rotation(x, d, k);
		find_same();
	}

	int res = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (board[i][j] != 0) {
				res += board[i][j];
			}
		}
	}
	cout << res << "\n";
	return 0;
}