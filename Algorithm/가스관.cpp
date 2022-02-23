#include <iostream>
#include <cstdlib>
using namespace std;

#define SIZE 30

int r{}, c{};
char map[SIZE][SIZE]{};
bool visited[SIZE][SIZE]{};
int mr{}, mc{}, zr{}, zc{};
int br{}, bc{};
char block{};

int dy[] = { 0,0,1,-1 };
int dx[] = { 1,-1,0,0 };

void init() {
    memset(visited, false, sizeof(visited));
}

void input_data() {
    cin >> r >> c;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> map[i][j];
            if (map[i][j] == 'M') {
                mr = i;
                mc = j;
            }
            else if (map[i][j] == 'Z') {
                zr = i;
                zc = j;
            }
        }
    }
}

// 블록이 있으면 방향대로 dfs 진행
//        없으면 방향에서 갈 수 있는 것만 . 대신 바꿔서 진행
void dfs(int y, int x, bool flag) {
    visited[y][x] = true;

    if (y == zr && x == zc) {
        return;
    }

    // flag 는 빈칸이 1개 지나쳤다는 표시
    if (flag) {
        int cnt = 0;
        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (ny < 0 || nx < 0 || ny >= r || nx >= c)   continue;
            if (map[ny][nx] == '.') {
                cnt++;
                continue;
            }
        }
        if (cnt == 4)   return;
    }

    // 현재 위치에 있는 기호에 따라 탐색
    // 맵변경 -> dfs -> 원상복귀
    if (map[y][x] == '|') {
        // 위 + 아래
        // 다음올 수 있는 기호는 + 2 3
    }
    else if (map[y][x] == '-') {
        // 왼 + 오른
        // 다음올 수 있는 기호는 + 1 2 3 4
    }
    else if (map[y][x] == '+') {
        // 4방향 탐색
        // 다음올 수 있는 기호는 | - + 1 2 3 4
    }
    else if (map[y][x] == '1') {
        // 오른 + 아래
        // 다음올 수 있는 기호는 | - + 2 3 4
    }
    else if (map[y][x] == '2') {
        // 위 + 오른 
    }
    else if (map[y][x] == '3') {
        // 위 + 왼
    }
    else if (map[y][x] == '4') {
        // 왼 + 아래
    }
}

void solution() {
    /*
    -> 빈칸에 7개를 모두 놔본다
    BigO = 25 * 25 * 7
    M -> 4방향에서 길이 있다면 -> 가보기 -> dfs
                길이 없다면 -> 7방향 모두 가보기 -> dfs
    */
    dfs(mr, mc, false);
}

int main() {

    init();

    input_data();

    solution();

    cout << br + 1 << bc + 1 << block << endl;
    return 0;
}