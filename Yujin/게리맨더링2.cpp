#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
int result = 987654321;
int dx[2] = {-1,1};
int dy[2] = {1,1};
int map[21][21];
int local[21][21];

void five(int y, int x, int d1, int d2){
	//5구역나누기
	if(d1+d2 > n-y || d2 > n-x || d1 > x-1) return;
	for(int i = y, j = x; i <= y+d1, j >= x-d1; i++, j--) local[i][j] = 5;
	for(int i = y, j = x; i <= y+d2, j <= x+d2; i++, j++) local[i][j] = 5;
	for(int i = y+d1, j = x-d1; i <= y+d1+d2, j <= x-d1+d2; i++, j++) local[i][j] = 5;
	for(int i = y+d2, j = x+d2; i <= y+d1+d2, j >= x+d2-d1; i++, j--) local[i][j] = 5;

	//5채우기
	for(int i = y+1; i < y+d1+d2; i++){
		for(int j = 1; j <= n; j++){
			if(local[i][j] == 5){
				int s = j+1;
				while(local[i][s] == 0){
					local[i][s] = 5;
					s++;
				}
				break;
			}
		}
	}

	//1234 라벨링
	for(int i = 1; i <= n; i++){ //y,r
		for(int j = 1; j <= n; j++){ //x,c
			if(1 <= i && i < y + d1 && 1 <= j && j <= x && local[i][j] != 5) local[i][j] = 1;
			else if(1 <= i && i <= y + d2 && x <= j && j <= n && local[i][j] != 5) local[i][j] = 2;
			else if(y + d1 <= i && i <= n && 1 <= j && j < x-d1+d2 && local[i][j] != 5) local[i][j] = 3;
			else if(y + d2 < i && i <= n && x-d1+d2 <= j && j <= n && local[i][j] != 5) local[i][j] = 4;
		}
	}

	return;
}

void cal(){
	int sum[5] = {0,};
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(local[i][j] == 1) sum[0] += map[i][j];
			else if(local[i][j] == 2) sum[1] += map[i][j];
			else if(local[i][j] == 3) sum[2] += map[i][j];
			else if(local[i][j] == 4) sum[3] += map[i][j];
			else sum[4] += map[i][j];
		}
	}
	sort(sum, sum+5);
	result = min(sum[4]-sum[0], result);
}


int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			cin >> map[i][j];
		}
	}

	//선거구 나누기
	for(int y = 1; y < n-1; y++){
		for(int x = 2; x < n; x++){
			for(int d1 = 1; d1 < x; d1++){
				for(int d2 = 1; d2 <= n-x; d2++){
					memset(local, 0, sizeof(local));
					five(y, x, d1, d2);
					cal();
				}
			}
		}
	}

	cout << result << endl;

	return 0;
}