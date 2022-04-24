#include<iostream>
#include<queue>
#include<string>
using namespace std;

int N, M, K;
int ans = 1;
bool flag;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };

queue < pair<pair<int, int>, int>>q;
int map[1001][1001];
bool visited[1001][1001][11];

int main(void)
{
    string str;

    cin >> N >> M >> K;

    for (int i = 1; i <= N; i++)
    {
        cin >> str;
        for (int j = 1; j <= M; j++)
        {
            map[i][j] = str[j - 1];
        }
    }

    q.push(make_pair(make_pair(1, 1), 0));
    visited[1][1][0] = true;


    while (!q.empty())
    {
        int qsize = q.size();
        while (qsize--)
        {
            int x = q.front().first.first;
            int y = q.front().first.second;
            int gowall = q.front().second;
            q.pop();

            if (x == N && y == M)
            {
                flag = true;
                break;
            }

            for (int i = 0; i < 4; i++)
            {
                int mx = x + dx[i];
                int my = y + dy[i];
                int ngowall = map[mx][my] - '0';

                if (mx >= 1 && mx <= N && my >= 1 && my <= M)
                {
                    if ((gowall + ngowall) > K) continue; // 벽을 k번 까지 부술 수 있다. k번이 넘어가면 continue
                    ngowall += gowall;
                    if (visited[mx][my][ngowall]) continue;
                    q.push(make_pair(make_pair(mx, my), ngowall));
                    visited[mx][my][ngowall] = true;
                }
            }
        }
        if (flag) break;
        else ans++;
    }

    if (flag) cout << ans;
    else cout << -1;

    return 0;
}
