#include <iostream>
#include <vector>

using namespace std;

int n, x, y, d, g;
int map[101][101];
int dy[4] = {0, -1, 0, 1};
int dx[4] = {1, 0, -1, 0};
int cnt;
vector<int> dir_info; // 드래곤커브의 방향정보를 저장하는 vector

void makeDragonCurve()
{
    int size = dir_info.size();
    for (int i = size - 1; i >= 0; i--)
    {
        int nd = (dir_info[i] + 1) % 4;
        y += dy[nd];
        x += dx[nd];
        map[y][x] = 1;
        dir_info.push_back(nd);
    }
}

// 모든 꼭지점이 드래곤커브인 정사각형 개수 세기
void countSquare()
{
    for (int i = 0; i < 101; i++)
    {
        for (int j = 0; j < 101; j++)
        {
            if (map[i][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j] == 1 && map[i + 1][j + 1] == 1)
                cnt++;
        }
    }
}

void solve()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    while (n--)
    {
        cin >> x >> y >> d >> g;
        dir_info.clear();

        // 0세대 드래곤커브 그리기
        map[y][x] = 1;
        y += dy[d];
        x += dx[d];
        map[y][x] = 1;

        dir_info.push_back(d);
        // g 세대의 드래곤커브 그리기
        while (g--)
        {
            makeDragonCurve();
        }
    }
    countSquare();
    cout << cnt << '\n';
}

int main()
{
    solve();

    return 0;
}