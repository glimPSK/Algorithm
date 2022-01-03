#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
using namespace std;

struct S_POS {
    int y{};
    int x{};
    int dir{};
};

int n{}, k{}, l{};
int map[120][120]{};
int t[120]{};
char c[120]{};
int nRes{};

// ¼­ - ºÏ - µ¿ - ³²
int dy[] = { 0, -1 ,0 ,1 };
int dx[] = { -1, 0 ,1, 0 };


int bfs() {
    queue <S_POS> Q{};
    Q.push({ 1,1, 2 });

    int time = 0;
    int idx = 0;
    map[1][1] = 2;

    int y = Q.front().y;
    int x = Q.front().x;
    int d = Q.front().dir;

    while (true) {
        y += dy[d];
        x += dx[d];

        time++;
        if (y < 1 || x < 1 || y > n || x > n || map[y][x] == 2) {
            return time;
        }

        if (map[y][x] == 0) {
            int ty = Q.front().y;
            int tx = Q.front().x;
            map[ty][tx] = 0;
            Q.pop();
        }
        if (time == t[idx]) {
            if (c[idx] == 'D') {
                d++;
                if (d > 3) {
                    d = 0;
                }
            }
            else {
                d--;
                if (d < 0) {
                    d = 3;
                }
            }
            idx++;
        }
        Q.push({ y,x,d });
        map[y][x] = 2;
    }
}

int main() {
    //input data
    scanf("%d", &n);
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        int y, x;
        scanf("%d %d", &y, &x);
        map[y][x] = 1;
    }
    scanf("%d", &l);
    for (int i = 0; i < l; i++) {
        scanf("%d %c", &t[i], &c[i]);
    }

    //logic
    int nRes = bfs();

    //result
    printf("%d\n", nRes);
    return 0;
}