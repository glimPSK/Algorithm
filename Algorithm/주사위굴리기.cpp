#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
using namespace std;

int n{}, m{}, y{}, x{}, k{};
int map[30][30]{};
int dice[7]{};

int dy[] = { 0,0,0,-1,1 };
int dx[] = { 0,1,-1,0,0 };

void moveDice(int num) {
	int temp[7]{};
	memcpy(temp, dice, sizeof(temp));

	if (num == 1) {
		dice[0] = temp[0];
		dice[1] = temp[4];
		dice[2] = temp[2];
		dice[3] = temp[5];
		dice[4] = temp[3];
		dice[5] = temp[1];
	}
	else if (num == 2) {
		dice[0] = temp[0];
		dice[1] = temp[5];
		dice[2] = temp[2];
		dice[3] = temp[4];
		dice[4] = temp[1];
		dice[5] = temp[3];
	}
	else if (num == 3) {
		dice[0] = temp[1];
		dice[1] = temp[2];
		dice[2] = temp[3];
		dice[3] = temp[0];
		dice[4] = temp[4];
		dice[5] = temp[5];
	}
	else if (num == 4) {
		dice[0] = temp[3];
		dice[1] = temp[0];
		dice[2] = temp[1];
		dice[3] = temp[2];
		dice[4] = temp[4];
		dice[5] = temp[5];
	}
}

void input_data() {
	cin >> n >> m >> y >> x >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
}

void solution() {
	//logic
	for (int i = 0; i < k; i++) {
		int dir;
		cin >> dir;

		int ny = y + dy[dir];
		int nx = x + dx[dir];

		if (ny < 0 || nx < 0 || ny >= n || nx >= m)	continue;

		// 변경된 주사위
		moveDice(dir);

		//바닥과 맞닿는 면 0인지 아닌지
		if (map[ny][nx] == 0) {
			map[ny][nx] = dice[3];
		}
		else {
			dice[3] = map[ny][nx];
			map[ny][nx] = 0;
		}
		y = ny;
		x = nx;
		cout << dice[1] << endl;
	}
}

int main() {
	//input
	input_data();

	//solve
	solution();


	return 0;
}