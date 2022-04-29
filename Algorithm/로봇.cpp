#include<iostream>
#include<queue>
using namespace std;

int R, C, k;
int room[1000][1000];
int visited[1000][1000];

int dir[4];
// 1 : ºÏ, 2 : ³², 3 : ¼­, 4 : µ¿
int dx[5] = { 0, -1, 1, 0, 0 };
int dy[5] = { 0, 0, 0, -1, 1 };

void simulate(int x, int y)
{
    int i = 0;
    int count = 0;
    int mx = 0;
    int my = 0;

    while (1)
    {
        if (count == 4) {
            cout << x << ' ' << y;
            return;
        }

        mx = x + dx[dir[i]];
        my = y + dy[dir[i]];

        if ((mx < 0 || mx >= R || my < 0 || my >= C) || visited[mx][my] || room[mx][my]) {
            i = (i + 1) % 4;
            count++;
            continue;
        }

        visited[mx][my] = 1;
        x = mx;
        y = my;
        count = 0;
    }
    return;
}

int main()
{
    int x = 0, y = 0;
    cin >> R >> C;
    cin >> k;

    for (int i = 0; i < k; i++)
    {
        cin >> x >> y;
        room[x][y] = 1;
    }

    cin >> x >> y;
    visited[x][y] = 1;

    for (int i = 0; i < 4; i++)
        cin >> dir[i];

    simulate(x, y);

    return 0;
}
