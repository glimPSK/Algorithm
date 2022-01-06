#include <iostream>
#include <algorithm>
using namespace std;

const int SIZE = 510;

int N, M;
int map[SIZE][SIZE];
bool v[SIZE][SIZE];

int dy[] = { 1,-1,0,0 };
int dx[] = { 0,0,1,-1 };

//전형적인 DFS
int dfs(int y, int x, int cnt) {
    if (cnt == 4)
        return map[y][x];

    int sum = 0;
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];

        if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
        if (!v[ny][nx]) {
            v[y][x] = true;
            sum = max(sum, map[y][x] + dfs(ny, nx, cnt + 1));
            v[y][x] = false; //꼭 처리해줘야한다
        }
    }
    return sum;
}

//DFS로 판별할 수 없는 테트로미노
int middleFinger(int y, int x) {
    int result = -987987987;

    //ㅗ (현재 좌표 ㅡ의 가운데)
    if (y >= 1 && x >= 1 && x < M - 1)
        result = max(result, map[y][x - 1] + map[y][x] + map[y - 1][x] + map[y][x + 1]);
    //ㅏ (현재 좌표 ㅣ의 가운데)
    if (y >= 1 && y < N - 1 && x < M - 1)
        result = max(result, map[y - 1][x] + map[y][x] + map[y][x + 1] + map[y + 1][x]);
    //ㅜ (현재 좌표 ㅡ의 가운데)
    if (y >= 0 && y < N - 1 && x < M - 1)
        result = max(result, map[y][x - 1] + map[y][x] + map[y + 1][x] + map[y][x + 1]);
    //ㅓ (현재 좌표 ㅣ의 가운데)
    if (y >= 1 && y < N - 1 && x >= 1)
        result = max(result, map[y - 1][x] + map[y][x] + map[y][x - 1] + map[y + 1][x]);

    return result;
}

void input_data() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }
}

void solution() {
    int nRes = -987987987;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            v[i][j] = true;
            nRes = max(nRes, dfs(i, j, 1));
            nRes = max(nRes, middleFinger(i, j));
            v[i][j] = false; //꼭 처리해줘야한다
        }
    }
    cout << nRes << endl;
}


int main() {
    //input
    input_data();

    //solve
    solution();

    return 0;
}
