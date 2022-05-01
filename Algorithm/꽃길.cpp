#include <iostream>
using namespace std;

int cost[10][10] = { 0 };
bool visit[10][10] = { false };
int n = 0;
int mini = 10000;
int di[4] = { 0, 0, 1 ,-1 };
int dj[4] = { 1,-1,0,0 };

bool whole_check(int i0, int j0) {
    if (visit[i0][j0]) {
        return false;
    }
    for (int idx = 0; idx < 4; idx++) {
        int i1 = i0 + di[idx];
        int j1 = j0 + dj[idx];
        if (i1<0 || i1>n - 1 || j1<0 || j1>n - 1 || visit[i1][j1]) {
            return false;
        }
    }
    return true;
}

void dfs(int count, int sum, int start_i) {
    if (count == 3) {
        if (mini > sum) {
            mini = sum;
        }
        return;
    }

    for (int i = start_i; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!whole_check(i, j)) {
                continue;
            }

            int s = cost[i][j];
            visit[i][j] = true;
            for (int idx = 0; idx < 4; idx++) {
                int i1 = i + di[idx];
                int j1 = j + dj[idx];
                visit[i1][j1] = true;
                s += cost[i1][j1];
            }

            dfs(count + 1, sum + s, i);

            visit[i][j] = false;
            for (int idx = 0; idx < 4; idx++) {
                int i1 = i + di[idx];
                int j1 = j + dj[idx];
                visit[i1][j1] = false;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &(cost[i][j]));
        }
    }
    dfs(0, 0, 1);
    cout << mini;
}