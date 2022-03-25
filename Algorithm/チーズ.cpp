/*
Q)  치즈를 순서대로 먹으면서 이동하는 최단거리

S)  1. 재방문 가능
    2. 낮은 순서 치즈부터 먹어가면서 이동해야함

A)  1. 맵입력
    2. N번, BFS ( 시작점 -> 1번 -> 2번치즈 순서대로 냠냠)
    3. 다시 BFS 할때마다, check[][]초기화
*/

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define SIZE 1010

struct S_POS {
    int y{};
    int x{};
    int dir{};
};

int R{}, C{}, N{};
int my{}, mx{}, nRes{}, hp = 1;
char map[SIZE][SIZE]{};
bool check[SIZE][SIZE]{};

int dy[] = { 0,0,1,-1 };
int dx[] = { 1,-1,0,0 };


void bfs() {
    queue <S_POS> q{};

    q.push({ my, mx, 0 });
    check[my][mx] = true;

    while (!q.empty()) {
        int y = q.front().y;
        int x = q.front().x;
        int d = q.front().dir;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (ny < 0 || ny >= R || nx < 0 || nx >= C) continue;
            if (check[ny][nx] || map[ny][nx] == 'X') continue;

            if ('1' <= map[ny][nx] && map[ny][nx] <= '9') {
                if (hp >= map[ny][nx] - '0') {
                    hp++;
                    map[ny][nx] = '.';
                    nRes += (d + 1);
                    my = ny;
                    mx = nx;
                    return;
                }
            }
            q.push({ ny, nx, d + 1 });
            check[ny][nx] = true;
        }
    }
}

void input_data() {
    cin >> R >> C >> N;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> map[i][j];
            if (map[i][j] == 'S') {
                my = i;
                mx = j;
            }
        }
    }
}

void solution() {
    for (int i = 0; i < N; i++) {
        memset(check, false, sizeof(check));
        bfs();
    }
    cout << nRes << endl;
}

int main() {
    input_data();
    solution();    
    return 0;
}
