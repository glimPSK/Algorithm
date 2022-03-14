/*
Q)   며칠이 지나야 백조들이 만날 수 있는지 계산

S)  1. R x C 행렬
    2. 물 공간과 접촉한 모든 빙판 공간은 녹는다. (대각선 고려 X)
    3 물 . / 빙판 X / 백조 L

A)  1. 백조 위치 파악
    2. 만날 수 있는지 없는지 판단
    3. (먼저 빙판을 모두 큐에 넣고 bfs) 빙판 녹이기 -> 상하좌우 물과 닿으면 큐에서 제거

*/

#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

#define SIZE 1505

int R{}, C{};
int nDay{};
char map[SIZE][SIZE]{};
bool visited[SIZE][SIZE]{};
bool check[SIZE][SIZE]{};

vector <pair<int, int>> ice{};
vector <pair<int, int>> swan{};

int dy[] = { 0,0,1,-1 };
int dx[] = { 1,-1,0,0 };

void input_data() {
    cin >> R >> C;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> map[i][j];
            //init
            if (map[i][j] == 'X') {
                ice.push_back(make_pair(i, j));
            }
            else if (map[i][j] == 'L') {
                swan.push_back(make_pair(i, j));
            }
        }
    }
}

bool isContact() {
    queue <pair<int, int>> q{};

    //init
    memset(visited, false, sizeof(visited));
    visited[swan[0].first][swan[0].second] = true;
    q.push(make_pair(swan[0].first, swan[0].second));

    while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        if (y == swan[1].first && x == swan[1].second) {
            return true;
        }

        for (int k = 0; k < 4; k++) {
            int ny = y + dy[k];
            int nx = x + dx[k];

            if (ny < 0 || nx < 0 || ny >= R || nx >= C) continue;
            if (!visited[ny][nx] && map[ny][nx] == '.') {
                q.push(make_pair(ny, nx));
                visited[ny][nx] = true;
            }
        }
    }
    return false;
}

void melting() {
    vector <pair<int, int>>::iterator iter{};

    //init
    memset(check, false, sizeof(check));

    // 물이 하나라도 있으면 check
    for (iter = ice.begin(); iter != ice.end(); iter++) {
        int y = (*iter).first;
        int x = (*iter).second;

        for (int k = 0; k < 4; k++) {
            int ny = y + dy[k];
            int nx = x + dx[k];

            if (ny < 0 || nx < 0 || ny >= R || nx >= C) continue;
            if (map[ny][nx] == '.') {
                check[y][x] = true;
                break;
            }
        }
    }

    // check[][] == true인것, 맵에서도 변경하고, ice에서 삭제
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (check[i][j]) {
                for (iter = ice.begin(); iter != ice.end(); iter++) {
                    if ((*iter).first == i && (*iter).second == j) {
                        map[i][j] = '.';
                        ice.erase(iter);
                        break;
                    }
                }
            }
        }
    }
}

void solution() {
    while (true) {
        if (isContact()) {
            cout << nDay << endl;
            return;
        }
        melting();
        nDay++;

        /*
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                cout << map[i][j];
            }
            cout << endl;
        }
        cout << endl << endl;
        */
    }
}

int main() {
    //init
    nDay = 0;

    //input
    input_data();

    //solution
    solution();
    return 0;
}