#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n;
int map[30][30];
int myMax = 0;

void merge(int dir) {
    queue <int> q;

    if (dir == 0) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (map[j][i] != 0) q.push(map[j][i]);
                map[j][i] = 0;
            }

            int idx = 0;
            int pop_data;

            while (!q.empty()) {
                pop_data = q.front();
                q.pop();

                if (map[idx][i] == 0) map[idx][i] = pop_data;
                else if (map[idx][i] == pop_data) {
                    map[idx][i] *= 2;
                    idx++;
                }
                else map[++idx][i] = pop_data;
            }

        }
    }
    else if (dir == 1) {
        for (int i = 0; i < n; i++) {
            for (int j = n - 1; j >= 0; j--) {
                if (map[j][i] != 0) q.push(map[j][i]);
                map[j][i] = 0;
            }

            int idx = n - 1;
            int pop_data;

            while (!q.empty()) {
                pop_data = q.front();
                q.pop();

                if (map[idx][i] == 0) map[idx][i] = pop_data;
                else if (map[idx][i] == pop_data) {
                    map[idx][i] *= 2;
                    idx--;
                }
                else map[--idx][i] = pop_data;
            }
        }
    }
    else if (dir == 2) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (map[i][j] != 0) q.push(map[i][j]);
                map[i][j] = 0;
            }

            int idx = 0;
            int pop_data;

            while (!q.empty()) {
                pop_data = q.front();
                q.pop();

                if (map[i][idx] == 0) map[i][idx] = pop_data;
                else if (map[i][idx] == pop_data) {
                    map[i][idx] *= 2;
                    idx++;
                }
                else map[i][++idx] = pop_data;
            }

        }
    }
    else if (dir == 3) {
        for (int i = 0; i < n; i++) {
            for (int j = n - 1; j >= 0; j--) {
                if (map[i][j] != 0) q.push(map[i][j]);
                map[i][j] = 0;
            }

            int idx = n - 1;
            int pop_data;

            while (!q.empty()) {
                pop_data = q.front();
                q.pop();

                if (map[i][idx] == 0) map[i][idx] = pop_data;
                else if (map[i][idx] == pop_data) {
                    map[i][idx] *= 2;
                    idx--;
                }
                else map[i][--idx] = pop_data;
            }
        }
    }
}


void dfs(int x) {
    if (x == 5) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                myMax = max(myMax, map[i][j]);
            }
        }
        return;
    }

    // map -> copy
    int cmap[30][30];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cmap[i][j] = map[i][j];
        }
    }

    //dfs
    for (int i = 0; i < 4; i++) {
        merge(i); // 방향보고 합침
        dfs(x + 1);
        // 위에서 저장했던 처음 map으로 변경
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                map[i][j] = cmap[i][j];
            }
        }

    }
}

int main() {
    //init
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &map[i][j]);
        }
    }

    //logic
    dfs(0);

    //result
    printf("%d", myMax);
    return 0;
}