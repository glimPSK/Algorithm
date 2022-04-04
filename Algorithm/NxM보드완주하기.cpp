/*
Q)	모든 칸을 방문하기 위한 이동 횟수(방향틀은) 최소값 구하기

S)	1. N, M <= 30

A)	1. DFS -> 방향바뀔 때 cnt ++ (모두방문체크)

참고) https://dmzld.tistory.com/33
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define SIZE 32
#define INF 987987987

int N{}, M{}, K{};
char map[SIZE][SIZE]{};
bool visited[SIZE][SIZE]{};

int dy[] = { 0,0,1,-1 };
int dx[] = { 1,-1,0,0 };

int ans;

void dfs(int y, int x, int cnt, int k) {
	// 조금이나마 시간 줄이기
	if (ans < cnt)	return;

	// 모두 탐색한 경우에 ans 갱신
	if (k == 0) {
		if (ans > cnt)	ans = cnt;
		return;
	}
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		int nk = k;
		// 현재 방향으로 탐색할 수 있을 때 까지 탐색
		while (ny >= 0 && ny < N && nx >= 0 && nx < M && map[ny][nx] == '.' && !visited[ny][nx]) {
			visited[ny][nx] = true;
			nk--;
			ny += dy[i];
			nx += dx[i];
		}
		ny -= dy[i];
		nx -= dx[i];

		if (ny != y || nx != x) {
			dfs(ny, nx, cnt + 1, nk);
			// 이번 반복문에서 탐색한 영역 되돌리기
			while (ny != y || nx != x) {
				visited[ny][nx] = false;
				ny -= dy[i];
				nx -= dx[i];
			}
		}
	}
}

int main() {
	int T = 1;
	while (cin >> N >> M) {
		// init
		ans = INF;
		K = 0;
		memset(visited, false, sizeof(visited));

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++) {
				cin >> map[i][j];
				if (map[i][j] == '.')
					K++; // 탐색되어야할 공간의 수
			}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] == '.') {
					visited[i][j] = true;
					dfs(i, j, 0, K - 1); // 재귀 시작
					visited[i][j] = false;
				}
			}
		}

		if (ans == INF)
			cout << "Case " << T << ": " << -1 << "\n";
		else
			cout << "Case " << T << ": " << ans << "\n";

		T++;
	}

	return 0;
}