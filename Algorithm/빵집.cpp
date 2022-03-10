/*
Q)	가스관과 빵집을 연결하는 파이프라인의 최대 개수 구해라

S)	1. 첫번째 열 : 빵집의 가스관
	2. 마지막 열 : 원웅이의 빵집
	3. 첫번째열과 마지막 열을 연결하는 파이프를 설치하려 함
	(* 단, 건물이 존재하면 파이프 설치 X)
	4. 오른쪽, 오른쪽 위 대각선, 오른쪽 아래 대각선 연결 가능

TC)
01x.443210
..23.x....

0xx..
.1x10
..2..
...x.
...x.

A)	1. R,C 입력
	2. BFS 제일 왼쪽 제일 오른쪽 다 담기
	3. visited check하며 진행 -> 다음에 값이 있다면 더하기 1 하고 종료
*/

#include <iostream>
#include <queue>
#include <string>
using namespace std;
#define SIZE 10010

int R{}, C{};
int map[SIZE][SIZE]{};
bool visited[SIZE][SIZE]{};


queue <pair<int, int>> Q{};

void input_data() {
	char temp;
	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> temp;
			if (temp == '.') {
				map[i][j] = 0;
			}
			else if (temp == 'x') {
				map[i][j] = -1;
			}
		}
	}
}

void bfs() {
	int nRes{};

	//init
	for (int i = 0; i < R; i++) {
		Q.push(make_pair(i, 0));
	}
	nRes = 0;
	// 오른 / 대각위 / 대각 아래 / 
	int dy[3] = { 0, -1, 1};
	int dx[3] = { 1, 1, 1 };

	while (!Q.empty()) {
		int y = Q.front().first;
		int x = Q.front().second;
		Q.pop();

		for (int k = 0; k < 3; k++) {
			int ny = y + dy[k];
			int nx = x + dx[k];
			if (ny < 0 || nx < 0 || ny >= R || nx >= C)	continue;
			if (!visited[ny][nx] && map[ny][nx] != -1) {
				Q.push(make_pair(ny, nx));
				map[ny][nx] = map[y][x] + 1;
				visited[ny][nx] = true;
				if (nx == C - 1)	return;
			}
		}
	}
}

void solution() {
	//init
	memset(visited, false, sizeof(visited));
	
	//logic
	bfs();

	//result
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cout << map[i][j] << "\t";
		}
		cout << endl;
	}
}

int main() {
	input_data();

	solution();

	return 0;
}