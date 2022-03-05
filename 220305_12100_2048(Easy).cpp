#include<iostream>
using namespace std;

int n, res;
int map[20][20];
int cmap[20][20];
int dir[5];
bool visit[20][20];

void Right()
{
    //일단 0없게 다 이동
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j > 0; j--) //오른쪽부터
        {
            bool check = false;
            if (cmap[i][j] == 0)
            {
                int k = j - 1;
                while (k >= 0)
                {
                    if (cmap[i][k] != 0)
                    {
                        check = true;
                        break;
                    }
                    k--;
                }
                if (check == true)
                {
                    cmap[i][j] = cmap[i][k];
                    cmap[i][k] = 0;
                }
            }
        }
    }

    //같은숫자 합치기
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j > 0; j--)
        {
            if (cmap[i][j] == cmap[i][j - 1])
            {
                cmap[i][j] = cmap[i][j] * 2;
                cmap[i][j - 1] = 0;
            }
        }
    }

    //0없게 다시 붙이기
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j > 0; j--)
        {
            bool check = false;
            if (cmap[i][j] == 0)
            {
                int k = j - 1;
                while (k >= 0)
                {
                    if (cmap[i][k] != 0)
                    {
                        check = true;
                        break;
                    }
                    k--;
                }
                if (check == true)
                {
                    cmap[i][j] = cmap[i][k];
                    cmap[i][k] = 0;
                }
            }
        }
    }
}

void Left()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            bool check = false;
            if (cmap[i][j] == 0)
            {
                int k = j + 1;
                while (k <= n - 1)
                {
                    if (cmap[i][k] != 0)
                    {
                        check = true;
                        break;
                    }
                    k++;
                }
                if (check == true)
                {
                    cmap[i][j] = cmap[i][k];
                    cmap[i][k] = 0;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (cmap[i][j] == cmap[i][j + 1])
            {
                cmap[i][j] = cmap[i][j] * 2;
                cmap[i][j + 1] = 0;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            bool check = false;
            if (cmap[i][j] == 0)
            {
                int k = j + 1;
                while (k <= n - 1)
                {
                    if (cmap[i][k] != 0)
                    {
                        check = true;
                        break;
                    }
                    k++;
                }
                if (check == true)
                {
                    cmap[i][j] = cmap[i][k];
                    cmap[i][k] = 0;
                }
            }
        }
    }
}

void Up()
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            bool check = false;
            if (cmap[i][j] == 0)
            {
                int k = i + 1;
                while (k <= n - 1)
                {
                    if (cmap[k][j] != 0)
                    {
                        check = true;
                        break;
                    }
                    k++;
                }

                if (check == true)
                {
                    cmap[i][j] = cmap[k][j];
                    cmap[k][j] = 0;
                }
            }
        }
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (cmap[i][j] == cmap[i + 1][j])
            {
                cmap[i][j] = cmap[i][j] * 2;
                cmap[i + 1][j] = 0;
            }
        }
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            bool check = false;
            if (cmap[i][j] == 0)
            {
                int k = i + 1;
                while (k <= n - 1)
                {
                    if (cmap[k][j] != 0)
                    {
                        check = true;
                        break;
                    }
                    k++;
                }

                if (check == true)
                {
                    cmap[i][j] = cmap[k][j];
                    cmap[k][j] = 0;
                }
            }
        }
    }
}

void Down()
{
    for (int i = n - 1; i > 0; i--)
    {
        for (int j = 0; j < n; j++)
        {
            bool check = false;
            if (cmap[i][j] == 0)
            {
                int k = i - 1;
                while (k >= 0)
                {
                    if (cmap[k][j] != 0)
                    {
                        check = true;
                        break;
                    }
                    k--;
                }
                if (check == true)
                {
                    cmap[i][j] = cmap[k][j];
                    cmap[k][j] = 0;
                }
            }
        }
    }

    for (int i = n - 1; i > 0; i--)
    {
        for (int j = 0; j < n; j++)
        {
            if (cmap[i - 1][j] == cmap[i][j])
            {
                cmap[i][j] = cmap[i][j] * 2;
                cmap[i - 1][j] = 0;
            }
        }
    }
    for (int i = n - 1; i > 0; i--)
    {
        for (int j = 0; j < n; j++)
        {
            bool check = false;
            if (cmap[i][j] == 0)
            {
                int k = i - 1;
                while (k >= 0)
                {
                    if (cmap[k][j] != 0)
                    {
                        check = true;
                        break;
                    }
                    k--;
                }
                if (check == true)
                {
                    cmap[i][j] = cmap[k][j];
                    cmap[k][j] = 0;
                }
            }
        }
    }

}

void start()
{
    //미리 선택한 방향대로 이동
    for (int i = 0; i < 5; i++)
    {
        if (dir[i] == 0) Right();
        else if (dir[i] == 1) Left();
        else if (dir[i] == 2) Down();
        else if (dir[i] == 3) Up();
    }

    //제일큰거 갱신
    int mmax = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (cmap[i][j] > mmax)
            {
                mmax = cmap[i][j];
            }
        }
    }
    if (res <= mmax) res = mmax;
}

void dfs(int idx, int cnt)
{
    if (cnt == 5)
    {
        //map 초기화
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cmap[i][j] = map[i][j];
            }
        }
        start();
        return;
    }

    //갈방향정해놓기
    for (int i = 0; i < 4; i++)
    {
        dir[cnt] = i;
        dfs(i, cnt + 1);
    }
}


int main(void)
{

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }

    dfs(0, 0);

    cout << res << endl;

    return 0;
}