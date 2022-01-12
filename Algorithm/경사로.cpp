#include <cstdio>

int N, L, ans;
int a[100][100];

void slope(int i, bool c) {
    int cnt = 1;
    for (int j = 0; j < N - 1; j++) {
        int d = c == 1 ? a[i][j + 1] - a[i][j] : a[j + 1][i] - a[j][i];
        if (d == 0) cnt++;
        else if (d == 1 && cnt >= L) cnt = 1;
        else if (d == -1 && cnt >= 0) cnt = -L + 1;
        else return;
    }
    if (cnt >= 0) ans += 1;
}

void solve() {
    for (int i = 0; i < N; i++) {
        slope(i, 1);
        slope(i, 0);
    }
    printf("%d\n", ans);
}

int main() {
    scanf("%d %d", &N, &L);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    solve();
    return 0;
}
