#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define SIZE 110

int n, m;
int map[SIZE][SIZE];
bool check[SIZE][SIZE];

int dy[] = { 0,0,1,-1 };
int dx[] = { 1,-1,0,0 };

void input_data() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> map[i][j];
        }
    }
}

int getCountCheese() {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] == 1) {
                cnt++;
            }
        }
    }
    return cnt;
}

void bfs() {
    queue <pair<int, int>> Q;

    //init
    memset(check, false, sizeof(check));
    check[0][0] = true;
    Q.push(make_pair(0, 0));

    //logic
    while (!Q.empty()) {
        int y = Q.front().first;
        int x = Q.front().second;
        Q.pop();

        for (int k = 0; k < 4; k++) {
            int ny = y + dy[k];
            int nx = x + dx[k];

            if (ny < 0 || nx < 0 || ny >= n || nx >= m)  continue;
            if (!check[ny][nx]) {
                if (map[ny][nx] == 0) {
                    Q.push(make_pair(ny, nx));
                }
                else if (map[ny][nx] == 1) {
                    map[ny][nx] = 0;
                }
                check[ny][nx] = true;
            }
        }
    }
}

void solution() {
    int time = 0;
    int cnt = 0;

    while (true) {
        int remain_cheese = getCountCheese();
        if (remain_cheese <= 0)   break;
        time++;
        cnt = remain_cheese;
        bfs();
    }

    //result
    cout << time << endl;
    cout << cnt << endl;
}

int main() {
    //input
    input_data();

    //solve
    solution();

    return 0;
}