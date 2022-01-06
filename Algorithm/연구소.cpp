#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

#define SIZE 10

int n{}, m{};
int myMax{};
int map[SIZE][SIZE]{};

int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };

void input_data() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
}

int bfs() {
	queue <pair<int, int>> Q{};
	bool check[10][10]{};

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 2) {
				check[i][j] = true;
				Q.push({ i,j });
			}
			else if (map[i][j] == 1) {
				check[i][j] = true;
			}
		}
	}
	// 바이러스 퍼트리기
	while (!Q.empty()) {
		int y = Q.front().first;
		int x = Q.front().second;
		Q.pop();

		for (int k = 0; k < 4; k++) {
			int ny = y + dy[k];
			int nx = x + dx[k];

			if (ny < 0 || nx < 0 || ny >= n || nx >= m) continue;
			if (!check[ny][nx]) {
				check[ny][nx] = true;
				Q.push(make_pair(ny, nx));
			}
		}
	}

	// 안전영역 구하기
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 0 && !check[i][j])	cnt++;
		}
	}
	return cnt;
}

void buildWall(int cnt) {
	if (cnt > 3)	return;
	if (cnt == 3) {
		myMax = max(myMax, bfs());
		return;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 0) {
				map[i][j] = 1;
				buildWall(cnt + 1);
				map[i][j] = 0;
			}
		}
	}
}

void solution() {
	//logic
	buildWall(0);

	//result
	cout << myMax;
}

int main() {
	//input
	input_data();

	//solve
	solution();

	return 0;
}