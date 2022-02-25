/*
# Q
- 원판을 T 번 회전시킨 후 원판에 적힌 수의 합은 ?
# Algo
- 1. i번째 회전할 때, Xi의 배수인 원판을 di 방향으로 ki칸 회전 (di // 0 : 시계 / 1 : 반시계)
- 2. 인접하면서 수가 같은 것을 모두 찾아서 지움
- 3. 없는 경우에는 원판에 적힌 수의 평균을 구함, 평균보다 큰 수에서 1을 빼고, 작은 수에는 1을 더함
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

#define SIZE 55

int n{}, m{}, t{};
int pan[SIZE][SIZE]{};
int nRes{};

int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };

void rotate(int x, int d, int k) {
	// 시계
	if (d == 0) {
		for (int i = 1; i <= k; i++) {
			int data = pan[x][m];
			for (int j = m; j > 1; j--) {
				pan[x][j] = pan[x][j - 1];
			}
			pan[x][1] = data;
		}
	}
	// 반시계
	else {
		for (int i = 1; i <= k; i++) {
			int data = pan[x][1];
			for (int j = 1; j < m; j++) {
				pan[x][j] = pan[x][j + 1];
			}
			pan[x][m] = data;
		}
	}
}

void  solution() {
	// 상하좌우 검색 시, 일치하면 v 배열에 -1 표시
	int v[SIZE][SIZE]{};
	bool flag = false;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			v[i][j] = pan[i][j];
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int k = 0; k < 4; k++) {
				int y = i + dy[k];
				int x = j + dx[k];
				if (y < 1 || x < 1 || y > n || x > m)	continue;
				if (pan[y][x] == 0) continue;
				if (pan[i][j] == pan[y][x]) {
					v[y][x] = 0;
					v[i][j] = 0;
					flag = true;
				}
			}
		}
		if (pan[i][1] != 0) {
			if (pan[i][1] == pan[i][m]) {
				v[i][1] = 0;
				v[i][m] = 0;
				flag = true;
			}
		}
	}

	if (!flag) {
		float avg = 0.0f;
		float sum = 0.0f;
		float cnt = 0.0f;

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (v[i][j] != 0) {
					sum += v[i][j];
					cnt++;
				}
			}
		}
		avg = sum / cnt;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (v[i][j] != 0) {
					if (v[i][j] > avg) v[i][j]--;
					else if (v[i][j] < avg) v[i][j]++;
				}
			}
		}
	}
	// update
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			pan[i][j] = v[i][j];
		}
	}
}

int main() {
	int x{}, d{}, k{};

	//input
	scanf("%d %d %d", &n, &m, &t);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &pan[i][j]);
		}
	}
	for (int i = 1; i <= t; i++) {
		scanf("%d %d %d", &x, &d, &k);
		//logic
		//x의 배수인 칸을 돌림
		int r = 1;
		while (x * r <= n) {
			rotate(x * r, d, k);
			r++;
		}
		solution();
	}

	//result
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (pan[i][j] != -1) {
				sum += pan[i][j];
			}
		}
	}
	if (sum < 0)	nRes = -1;
	else	nRes = sum;

	printf("%d\n", nRes);

	return 0;
}