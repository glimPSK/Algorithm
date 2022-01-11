#include <iostream>
using namespace std;

#define SIZE 52

int n{}, m{};
int map[SIZE][SIZE]{};
int ry{}, rx{}, rd{};
int cnt{};

// 북동남서(전진)
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };

void input_data() {
	cin >> n >> m;
	cin >> ry >> rx >> rd;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
}

void dfs(int y, int x, int dir) {
	//벽
	if (map[y][x] == 1)	return;

	//빈칸
	if (map[y][x] == 0) {
		//청소한 구역 -> 5로 바꿈
		map[y][x] = 2;
		cnt++;
	}

	// 4 방향 검사
	for (int k = 0; k < 4; k++) {
		int ndir = dir - 1 < 0 ? 3 : dir - 1;
		int ny = y + dy[ndir];
		int nx = x + dx[ndir];

		// 다음 칸으로 넘어간 경우 나머지 검사 X
		if (map[ny][nx] == 0) {
			dfs(ny, nx, ndir);
			return;
		}
		else {
			// 청소를 했거나 벽이면 방향만 바꿈
			dir = ndir;
		}
	}

	// 네 방향 모두 청소했거나 벽이면 방향을 유지한채로 후진
	int ndir = (dir + 2) % 4;
	dfs(y + dy[ndir], x + dx[ndir], dir);
}

void solution() {

	//logic
	dfs(ry, rx, rd);

	//result
	cout << cnt << endl;
}

int main() {
	//init
	cnt = 0;

	//input
	input_data();
	
	//solve
	solution();

	return 0;
}