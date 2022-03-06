#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

#define SIZE 21

struct info {
    int x, y, d, die;
}shark[SIZE * SIZE];

int n, m, k;
int arr[SIZE][SIZE];
int num;
int smell[SIZE][SIZE][3];
int visit[SIZE * SIZE];
int nRes = -1;  // 1: 상어번호 2: 냄새남은시간

int dx[] = { 0,-1,1,0,0 };
int dy[] = { 0,0,0,-1,1 };
int shark_dir[SIZE * SIZE][5][5]; // 1: 위 2: 아래 3: 좌 4: 우

void update() {
    for (int i = 1; i <= m; i++) {
        if (shark[i].die == 1) continue;
        for (int j = i; j <= m; j++) {
            if (i == j) continue;
            if (shark[i].x == shark[j].x && shark[i].y == shark[j].y) {
                if (i < j) shark[j].die = 1;
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        if (shark[i].die != 1) {
            smell[shark[i].x][shark[i].y][1] = i;
            smell[shark[i].x][shark[i].y][2] = k;
        }
    }
}

void solve(int num) {
    int x = shark[num].x;
    int y = shark[num].y;
    int d = shark[num].d;
    bool flag = false;

    for (int i = 1; i <= 4; i++) {
        int kx = x + dx[shark_dir[num][d][i]];
        int ky = y + dy[shark_dir[num][d][i]];
        if (kx < 0 || kx >= n || ky < 0 || ky >= n) continue;
        if (smell[kx][ky][2] == 0) {
            flag = true;
            shark[num].x = kx, shark[num].y = ky;
            shark[num].d = shark_dir[num][d][i];
            break;
        }
    }

    if (!flag) {
        for (int i = 1; i <= 4; i++) {
            int kx = x + dx[shark_dir[num][d][i]];
            int ky = y + dy[shark_dir[num][d][i]];
            if (kx < 0 || kx >= n || ky < 0 || ky >= n) continue;
            if (smell[kx][ky][1] == num) {
                shark[num].x = kx, shark[num].y = ky;
                shark[num].d = shark_dir[num][d][i]; // 이동할 곳이 없을때 방향을 이렇게 처리
                break;
            }
        }
    }
}

int main() {
    //input data
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[i][j]);
            if (arr[i][j] != 0) {
                shark[arr[i][j]].x = i, shark[arr[i][j]].y = j;
                smell[i][j][1] = arr[i][j], smell[i][j][2] = k;
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", &shark[i].d);
    }
    for (int e = 1; e <= m; e++) {
        for (int i = 1; i <= 4; i++) {
            for (int j = 1; j <= 4; j++) {
                scanf("%d", &shark_dir[e][i][j]);
            }
        }
    }

    //logic
    for (int t = 0; t < 1001; t++) {
        //counting shark
        int nCnt = 0;
        for (int i = 2; i <= m; i++) {
            if (shark[i].die == 1) nCnt++;
        }
        if (nCnt == m - 1) {
            nRes = t;
            break;
        }
        //moving shark
        for (int j = 1; j <= m; j++) {
            if (shark[j].die == 1) continue;
            solve(j);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (smell[i][j][2] > 0) smell[i][j][2]--;
                if (smell[i][j][2] == 0) smell[i][j][1] = 0;
            }
        }
        update();
    }
    printf("%d\n", nRes);
    return 0;
}