/*
Q)	가스관과 빵집을 연결하는 파이프라인의 최대 개수 구해라

S)	1. 첫번째 열 : 빵집의 가스관
	2. 마지막 열 : 원웅이의 빵집
	3. 첫번째열과 마지막 열을 연결하는 파이프를 설치하려 함
	(* 단, 건물이 존재하면 파이프 설치 X)
	4. 오른쪽, 오른쪽 위 대각선, 오른쪽 아래 대각선 연결 가능

A)	1. 오른쪽 위/오른 /오른쪽 아래 순으로 탐색 ( 재탐색 X)
	2. dfs 사용하여 해당 거리에서 갈 수 있는 방향을 재판단 하도록 구현할 것
	3. 빵집에 도달하게 되면 ( c == C-1 ) count++;
*/

#include <iostream>
using namespace std;
#define SIZE 10010

int R{}, C{};
int nCnt;
int map[SIZE][510]{};

int dr[] = { -1,0,1 };
int dc[] = { 1,1,1 };

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
				map[i][j] = 1;
			}
		}
	}
}

bool dfs(int r, int c) {
	if (c == C - 1) {
		nCnt++;
		return true;
	}

	map[r][c] = 1;
	for (int k = 0; k < 3; k++) {
		int nr = r + dr[k];
		int nc = c + dc[k];
		if (nr < 0 || nc < 0 || nr >= R || nc >= C)	continue;
		if (!map[nr][nc]) {
			if (dfs(nr, nc)) {
				return true;
			}
		}
	}
	return false;
}

void solution() {
	//logic
	for (int i = 0; i < R; i++) {
		dfs(i, 0);
	}

	//result
	cout << nCnt;
}

int main() {
	input_data();

	solution();

	return 0;
}