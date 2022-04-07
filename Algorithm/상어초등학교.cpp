#include <iostream>
using namespace std;

#define SIZE 20

struct S_STUDENT {
	int me{};
	int fri[4]{};
	int y{};
	int x{};
};

int n{};
int board[SIZE][SIZE]{};

S_STUDENT stu[400]{};

int dy[] = { 0,0,1,-1 };
int dx[] = { 1,-1,0,0 };

void input_data() {
	cin >> n;
	for (int i = 0; i < n * n; i++) {
		cin >> stu[i].me;
		for (int j = 0; j < 4; j++) {
			cin >> stu[i].fri[j];
		}
	}
}

int getPoint(int y, int x, int idx) {
	int point = 0;

	// 상하좌우 보면서 포인트 미리 계산
	for (int d = 0; d < 4; d++) {
		int ny = y + dy[d];
		int nx = x + dx[d];

		if (ny < 0 || nx < 0 || ny >= n || nx >= n)	continue;

		if (board[ny][nx] == 0) {
			point++;
		}
		else {
			for (int k = 0; k < 4; k++) {
				if (board[ny][nx] == stu[idx].fri[k]) {
					point += 10;
				}
			}
		}
	}
	return point;
}
void setStudent(int y, int x, int idx) {
	stu[idx].y = y;
	stu[idx].x = x;
	board[y][x] = stu[idx].me;
}


int getResult() {
	int nRes = 0;
	for (int i = 0; i < n * n; i++) {
		int point = 0;
		int y = stu[i].y;
		int x = stu[i].x;

		for (int d = 0; d < 4; d++) {
			int ny = y + dy[d];
			int nx = x + dx[d];
			if (ny < 0 || nx < 0 || ny >= n || nx >= n)	continue;

			for (int f = 0; f < 4; f++) {
				if (board[ny][nx] == stu[i].fri[f]) {
					if (point == 0) {
						point++;
					}
					else {
						point *= 10;
					}
				}
			}
		}
		nRes += point;
	}

	return nRes;
}

void solution() {
	// 제일 많이 비었다 판단
	// 각 자리에 대한 계산
	for (int i = 0; i < n * n; i++) {
		int curY = -1;
		int curX = -1;
		int point = -1;

		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				// i번째 학생이 (y,x)에 위치했을 때 포인트 계산
				int curPoint = getPoint(y, x, i);
				if (board[y][x] == 0) {
					if (point < curPoint) {
						curY = y;
						curX = x;
						point = curPoint;
					}
				}
			}
		}
		// i번째 학생 배치 시키기
		setStudent(curY, curX, i);
	}

	int nRes = getResult();
	cout << nRes << endl;
}

int main() {
	input_data();
	solution();
	return 0;
}