/*
Q)  최소로 움직인 횟수 구해라

A)  1. BFS -> 도착점 가장먼저 도착하면 최소
*/

#include<iostream>
#include<cstring>
#include<queue>

#define SIZE 300
using namespace std;

int l{};
bool visited[SIZE][SIZE]{};

int dx[] = { -1, -2, -2, -1, 1, 2, 2, 1 };
int dy[] = { -2, -1, 1, 2, 2, 1, -1, -2 };

pair <int, int> sPos{}, ePos{};

void Input_data() {
    cin >> l;
    cin >> sPos.first >> sPos.second;
    cin >> ePos.first >> ePos.second;
}

void BFS(int mx, int my) {
    queue<pair<pair<int, int>, int >> Q{};
    Q.push(make_pair(make_pair(mx, my), 0));
    visited[mx][my] = true;

    while (!Q.empty()) {
        int x = Q.front().first.first;
        int y = Q.front().first.second;
        int nCnt = Q.front().second;
        Q.pop();

        if (x == ePos.first && y == ePos.second) {
            cout << nCnt << endl;
            return;
        }

        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < l && ny < l) {
                if (!visited[nx][ny]) {
                    visited[nx][ny] = true;
                    Q.push(make_pair(make_pair(nx, ny), nCnt + 1));
                }
            }
        }
    }
}

void solution() {
    int tc{};
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        //init
        memset(visited, false, sizeof(visited));
        Input_data();
        BFS(sPos.first, sPos.second);
    }
}

int main(void) {
    solution();
    return 0;
}