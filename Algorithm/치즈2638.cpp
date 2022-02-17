#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#define SIZE 101
using namespace std;

typedef pair<int, int> node;

int n, m, ans;
int map[SIZE][SIZE];
int air[SIZE][SIZE];
bool visited[SIZE][SIZE];

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

vector<node> melted;

void printMap() {
    cout << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void bfs() {
    queue<node> Q;
    Q.push(node(0, 0));
    visited[0][0] = true;

    while (!Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;

            // 공기라면
            if (map[nx][ny] == 0 && !visited[nx][ny]) {
                Q.push(node(nx, ny));
                visited[nx][ny] = true;
            }
            // 치즈라면
            else if (map[nx][ny] == 1) {
                air[nx][ny] += 1;

                // 치즈가 녹을 예정이면?
                if (air[nx][ny] >= 2 && !visited[nx][ny]) {
                    melted.push_back(node(nx, ny));
                    visited[nx][ny] = true;
                }
            }
        }

        if (Q.empty()) {
            if (!melted.empty()) ans++;
            else break;

            for (int i = 0; i < melted.size(); i++) {
                Q.push(melted[i]);
                map[melted[i].first][melted[i].second] = 0;
            }
            melted.clear();
        }
    }
}

int main(int argc, const char* argv[]) {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> map[i][j];
        }
    }

    memset(visited, false, sizeof(visited));
    ans = 0;
    bfs();

    cout << ans << "\n";
    return 0;
}