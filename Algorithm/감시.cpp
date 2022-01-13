// 15683 / 감시
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int SIZE = 10;
const int INF = 987987987;

struct S_INFO {
	int y;
	int x;
	int num;
};

int n, m;
int map[SIZE][SIZE];
int nRes;

vector <S_INFO> cctv;

// 북 서 남 동
int dy[] = { -1,0,1,0 };
int dx[] = { 0,-1,0,1 };

// 사각지대 검사
int getResult() {
	int nCnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 0)	nCnt++;
		}
	}
	return nCnt;
}

void changeMap(int y, int x, int dir) {
	dir %= 4;

	if (dir == 0) {
		for (int i = y; i + dy[dir] >= 0; i += dy[dir]) {
			if (map[i + dy[dir]][x] == 6)	return;
			map[i + dy[dir]][x] = -1;
		}
	}
	else if (dir == 1) {
		for (int i = x; i + dx[dir] >= 0; i += dx[dir]) {
			if (map[y][i + dx[dir]] == 6)	break;
			map[y][i + dx[dir]] = -1;
		}
	}
	else if (dir == 2) {
		for (int i = y; i + dy[dir] < n; i += dy[dir]) {
			if (map[i + dy[dir]][x] == 6)	break;
			map[i + dy[dir]][x] = -1;
		}
	}
	else if (dir == 3) {
		for (int i = x; i + dx[dir] < m; i += dx[dir]) {
			if (map[y][i + dx[dir]] == 6)	break;
			map[y][i + dx[dir]] = -1;
		}
	}
}

// 맵 백업 -> 방향별로 돌아가면서 체크 -> 원상 복구
void recursion(int idx) {
	//escape condition
	if (idx == cctv.size()) {
		nRes = min(nRes, getResult());
		return;
	}

	//backup map
	int cMap[SIZE][SIZE];
	memcpy(cMap, map, sizeof(map));

	int y = cctv[idx].y;
	int x = cctv[idx].x;
	int num = cctv[idx].num;

	//logic
	if (num == 1) {
		for (int d = 0; d < 4; d++) {
			changeMap(y, x, d);
			recursion(idx + 1);
			memcpy(map, cMap, sizeof(map));
		}
	}
	else if (num == 2) {
		for (int d = 0; d < 4; d++) {
			changeMap(y, x, d);
			changeMap(y, x, d + 2);
			recursion(idx + 1);
			memcpy(map, cMap, sizeof(map));
		}
	}
	else if (num == 3) {
		for (int d = 0; d < 4; d++) {
			changeMap(y, x, d);
			changeMap(y, x, d + 1);
			recursion(idx + 1);
			memcpy(map, cMap, sizeof(map));
		}
	}
	else if (num == 4) {
		for (int d = 0; d < 4; d++) {
			changeMap(y, x, d);
			changeMap(y, x, d + 1);
			changeMap(y, x, d + 3);
			recursion(idx + 1);
			memcpy(map, cMap, sizeof(map));
		}
	}
	else if (num == 5) {
		for (int d = 0; d < 4; d++) {
			changeMap(y, x, d);
		}
		recursion(idx + 1);
	}
}


void solution() {
	//init
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] >= 1 && map[i][j] <= 5) {
				cctv.push_back({ i,j,map[i][j] });
			}
		}
	}
	nRes = INF;

	//logic
	recursion(0);

	//result
	cout << nRes << endl;
}

int main() {
	//input data
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	//logic
	solution();
}