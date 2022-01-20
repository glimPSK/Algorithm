#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct point {
    int y;
    int x;
};

int n{};
int l{}, r{};
int nRes{};

int map[64][64]{};
int temp[64][64]{};

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

void bfs(point pp) {
    queue <point> Q{};
    queue <point> L{};

    int v[64][64]{};
    int sum = map[pp.y][pp.x];

    v[pp.y][pp.x] = 1;

    Q.push(pp);
    L.push(pp);

    while (!Q.empty()) {
        point cur = Q.front();
        Q.pop();

        for (int i = 0; i < 4; i++) {
            point p = { cur.y + dy[i], cur.x + dx[i] };

            if (p.y < 0 || p.x < 0 || p.y >= n || p.x >= n) continue;
            //calculation
            int data = abs(map[p.y][p.x] - map[cur.y][cur.x]);
            //printf("data - %d\n", data);
            if (l <= data && data <= r && !v[p.y][p.x]) {
                sum += map[p.y][p.x];
                v[p.y][p.x] = 1;
                Q.push(p);
                L.push(p);
            }
        }
    }

    int nData = sum / L.size();
    while (!L.empty()) {
        temp[L.front().y][L.front().x] = nData;
        L.pop();
    }
}

bool isMigrate(point cur) {
    for (int i = 0; i < 4; i++) {
        point p = { cur.y + dy[i], cur.x + dx[i] };

        if (p.y < 0 || p.x < 0 || p.y >= n || p.x >= n) continue;
        //calculation
        int data = abs(map[p.y][p.x] - map[cur.y][cur.x]);
        if (l <= data && data <= r) return true;
    }
    return false;
}

int solve() {
    int nCnt = 0;

    while (true) {
        bool flag = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                temp[i][j] = map[i][j];
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (isMigrate({ i,j })) {
                    bfs({ i,j });
                    flag = true;
                }
            }
        }
        if (!flag)   break;

        nCnt++;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                map[i][j] = temp[i][j];
            }
        }
    }
    return nCnt;
}

int main() {
    // Input Data
    scanf("%d %d %d", &n, &l, &r);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &map[i][j]);
        }
    }
    // Logic
    nRes = solve();

    // Result
    printf("%d\n", nRes);

    // Test
    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
    */
    return 0;
}