#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
using namespace std;

#define INF 987987987

int n, m, h;
int nRes = INF;
int v[34][34];

bool check() {
    for (int i = 1; i <= n; i++) {
        int s = i;
        for (int j = 1; j <= h; j++) {
            if (v[j][s])s++;
            else if (v[j][s - 1])s--;
        }
        if (s != i) return false;
    }
    return true;
}

void solve(int cur, int cnt) {
    if (cnt > 3) return;
    if (check()) {
        nRes = min(nRes, cnt); return;
    }
    for (int i = cur; i <= h; i++) {
        for (int j = 1; j <= n; j++) {
            if (v[i][j] || v[i][j - 1] || v[i][j + 1]) continue;
            v[i][j] = 1;
            solve(i, cnt + 1);
            v[i][j] = 0;
        }
    }
}
int main() {
    int a{}, b{};

    //Input Data
    scanf("%d %d %d", &n, &m, &h);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        v[a][b] = 1;
    }

    //Logic
    solve(1, 0);

    //Result
    nRes = (nRes == INF) ? -1 : nRes;
    printf("%d", nRes);
    return 0;
}