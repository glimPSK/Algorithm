/*
Q)	전선 길이의 최솟값을 구해라.

S)	1. A1,A2 / B1,B2 전선을 이용해서 이으려고 한다.
	2. 두 직선은 접하면 안된다.

A)	1. N , M 입력 -> (* y, x 순이 아닌, x y 순임)
	2. 각 좌표 저장
		2-1) A1, A2, B1, B2
	3. A/B선을 잇는데 -> 방향 판단 방향 변경시 거리 + 2
		3-1) 서로 잇기 (단,겹치지않고) -> getDistance() 로 거리 받기
*/

#include <iostream>
#include <memory.h>
#define SIZE 110
using namespace std;

struct CONNECT {
    int x{};
    int y{};
    int bf{};
};

int map[SIZE][SIZE]{};
int check[4][SIZE][SIZE]{};
int A[SIZE][SIZE]{}, B[SIZE][SIZE]{};
int N{}, M{};
int st{}, ed{}, ix{}, iy{}, nx{}, ny{};
int A1x{}, A1y{}, A2x{}, A2y{}, B1x{}, B1y{}, B2x{}, B2y{};
int tmp{};
int nRes = 987987987;

CONNECT q[SIZE * SIZE]{};

int dx[] = { 0, 0, -1, 1 };
int dy[] = { -1, 1, 0, 0 };

void bfs(int d, int stx, int sty, int edx, int edy) {
    st = ed = -1;
    q[++st].x = stx; q[st].y = sty; q[st].bf = -1; check[d][sty][stx] = 1;
    while (st != ed) {
        ix = q[++ed].x; iy = q[ed].y;
        if (ix == edx && iy == edy) return;
        for (int i = 0; i < 4; i++) {
            nx = ix + dx[i]; ny = iy + dy[i];
            if (nx < 0 || ny < 0 || nx > M || ny > N || check[d][ny][nx]) continue;
            q[++st].x = nx; q[st].y = ny; q[st].bf = ed; check[d][ny][nx] = 1;
        }
    }
}

bool find(int stx, int sty, int edx, int edy, int arr[SIZE][SIZE]) {
    if (arr[sty][stx]) return false;
    st = ed = -1;
    q[++st].x = stx; q[st].y = sty; arr[sty][stx] = 1;
    while (st != ed) {
        ix = q[++ed].x; iy = q[ed].y;
        if (ix == edx && iy == edy) { tmp += arr[iy][ix]; return true; }
        for (int i = 0; i < 4; i++) {
            nx = ix + dx[i]; ny = iy + dy[i];
            if (nx < 0 || ny < 0 || nx > M || ny > N) continue;
            if (arr[ny][nx]) continue;
            q[++st].x = nx; q[st].y = ny; arr[ny][nx] = arr[iy][ix] + 1;
        }
    }
    return false;
}

void connect(int arr[SIZE][SIZE]) {
    int k = ed;
    while (k > -1) {
        arr[q[k].y][q[k].x] = -1;
        tmp++;
        k = q[k].bf;
    }
}

void input_data() {
    cin >> M >> N;
    cin >> A1x >> A1y >> A2x >> A2y;
    cin >> B1x >> B1y >> B2x >> B2y;
}

void init() {
    check[0][B1y][B1x] = -1;
    check[0][B2y][B2x] = -1;
    check[1][A1y][A1x] = -1;
    check[1][A2y][A2x] = -1;
}

void solution() {
    bfs(0, A1x, A1y, A2x, A2y);
    connect(A);
    if (find(B1x, B1y, B2x, B2y, A) && nRes > tmp) nRes = tmp;
    
    tmp = 0;
    
    bfs(1, B1x, B1y, B2x, B2y);
    connect(B);
    if (find(A1x, A1y, A2x, A2y, B) && nRes > tmp) nRes = tmp;

    //result
    if (nRes == 987987987) cout << "IMPOSSIBLE" << endl;
    else cout << nRes - 2 << endl;
}

int main() {
    input_data();
    init();
    solution();
    return 0;
}
