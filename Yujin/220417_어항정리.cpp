#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

int n, k;
int res;
int map[101][101];
int map2[101][101];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
int visited[101][101];

void comp(int y, int x) {
	visited[y][x] = 1;
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (map[ny][nx] == 0) continue;
		if (visited[ny][nx] == 1) continue;
		int d = abs(map[y][x] - map[ny][nx]) / 5;
		if (d > 0) {
			if (map[y][x] > map[ny][nx]) {
				map2[y][x] -= d;
				map2[ny][nx] += d;
			}
			else if (map[y][x] < map[ny][nx]) {
				map2[ny][nx] -= d;
				map2[y][x] += d;
			}
		}
	}
}
void add_fish() {
	int min_val = map[n][1];
	for (int i = 2; i <= n; i++) {
		if (min_val > map[n][i]) min_val = map[n][i];
	}

	for (int i = 1; i <= n; i++) {
		if (map[n][i] == min_val) map[n][i] += 1;
	}
}

void accum() {
	int start, width, height;

	start = width = height = 1;

	int i = 0;
	while (1)
	{
		if (start + width + height - 1 > n) break;

		for (int c = start; c < start + width; c++)
		{
			for (int r = n; r > n - height; r--)
			{
				int nr, nc;

				nr = n - width + c - start;
				nc = start + width + n - r;

				map[nr][nc] = map[r][c];
				map[r][c] = 0;
			}
		}

		if (i % 2) width++;
		else height++;

		start += (i / 2 + 1);

		i++;
	}
}

void adjust() {
	memcpy(map2, map, sizeof(map2));
	memset(visited, 0, sizeof(visited));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j] > 0) {
				comp(i, j);
			}
		}
	}
	memcpy(map, map2, sizeof(map));
}

void setLine() {
	memset(map2, 0, sizeof(map2));
	int cnt = 1;
	for (int j = 1; j <= n; j++) {
		for (int i = n; i >= 1; i--) {
			if (map[i][j] != 0) {
				map2[n][cnt] = map[i][j];
				cnt++;
			}
		}
	}
	memcpy(map, map2, sizeof(map));
}

void fold() {
	int sc = n / 2 + 1;
	for (int c = n / 2; c >= 1; c--) map[n - 1][sc++] = map[n][c];
	for (int c = n / 2; c >= 1; c--) map[n][c] = 0;

	for (int r = n - 1; r <= n; r++)
	{
		int ec = n / 4 * 3;
		int fix = n;
		for (int c = n / 2 + 1; c <= ec; c++)
		{
			int nr, nc;

			nr = 2 * n - r - 3;
			nc = fix--;

			map[nr][nc] = map[r][c];
			map[r][c] = 0;
		}
	}
}

void reorder(int cnt) {

	while (1) {
		//어항 물고기 수 차이가 k보다 작거나 같으면 return cnt
		int max_fish = 0, min_fish = 999999;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (map[i][j] == 0) continue;
				if (map[i][j] > max_fish) max_fish = map[i][j];
				if (map[i][j] < min_fish) min_fish = map[i][j];
			}
		}

		if (max_fish - min_fish <= k) {
			res = cnt;
			return;
		}

		//1. 물고기수 가장작은어항 +1
		add_fish();
		//2. 어항쌓기
		accum();
		//3. 어항물고기수 조절
		adjust();
		//4. 어항바닥에 일렬로
		setLine();
		//5. 공중부양 n/2, 두번
		fold();
		//3. 어항물고기수 조절
		adjust();
		//4. 바닥에 일렬로
		setLine();
		cnt++;
	}

}

int main() {

	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> map[n][i];
	}

	reorder(0);

	cout << res;
	return 0;
}