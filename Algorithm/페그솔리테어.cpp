/*
Q)	핀의 개수를 최소로 하기 위해 필요한 최소 이동횟수를 구해라

S)	1. 수평 수직방향으로 인접한 핀을 뛰어넘을 수 있다.
	2. 그 핀의 다음 칸으로 이동하는 것 만 허용
	3. 인접한  핀의 다음칸은 비어야함  그 인접핀은 제거됨

A)  1. 범위 체크
    2. dfs 진행
        2-1. o아니면 반복 -> o 다음칸 빈칸인지 체크
        2-2. 이동 -> 탐색 -> 복구
*/
#include <iostream>
#include <vector>
#define MAX 987654321
using namespace std;

const int row = 5;
const int col = 9;

int ansPin{};
int ansMove{};
char map[10][10]{};
int pinNum{};

int dy[] = { 0, 1, 0, -1 };
int dx[] = { 1, 0, -1, 0 };

void dfs(int y, int x, int pinNum, int depth) {
    if (pinNum <= ansPin) {
        if (pinNum == ansPin) {
            ansMove = (ansMove > depth ? depth : ansMove);
        }
        else {
            ansPin = pinNum; ansMove = depth; 
        }
    }

    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        // 다음칸 범위체크
        if (ny >= 0 && ny < row && nx >= 0 && nx < col) {
            // 'o'가 아니면 다음반복
            if (map[ny][nx] != 'o') continue;
            // 'o'면 그다음칸 빈칸인지 체크하고 이동
            int nny = ny + dy[i];
            int nnx = nx + dx[i];
            // 다다음칸 범위체크
            if (nny >= 0 && nny < row && nnx >= 0 && nnx < col) {
                if (map[nny][nnx] == '.') {
                    //이동
                    map[y][x] = map[ny][nx] = '.';
                    map[nny][nnx] = 'o';
                    // 0, 0부터 탐색을 해줘야한다.
                    for (int i = 0; i < row; i++)
                        for (int j = 0; j < col; j++)
                            if (map[i][j] == 'o')
                                dfs(i, j, pinNum - 1, depth + 1);
                    // 복구
                    map[y][x] = map[ny][nx] = 'o';
                    map[nny][nnx] = '.';
                }
            }
        }
    }
}
void solution() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (map[i][j] == 'o') {
                dfs(i, j, pinNum, 0);
            }
        }
    }
    printf("%d %d\n", ansPin, ansMove);
}

void input_data() {
    pinNum = 0;
    ansPin = ansMove = MAX;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> map[i][j];
            if (map[i][j] == 'o') pinNum++;
        }
    }
}
int main(void) {
    int T{};
    cin >> T;
    for (int t = 0; t < T; t++) {
        input_data();
        solution();
    }
}
