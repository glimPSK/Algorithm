#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define SIZE 26

int R{}, C{}, dir{};
char map[SIZE][SIZE]{};

vector <pair <int, int>> v{};

// ¡è 0  ¡é 1  ¡ç 2  ¡æ 3
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

void result(int y, int x) {
	cout << y << " " << x << " ";
	bool visited[4]{};

	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny <= 0 || ny > R || nx <= 0 || nx > C) continue;

		if (map[ny][nx] != '.') {
			if (i == 0 && (map[ny][nx] == '|' || map[ny][nx] == '+' || map[ny][nx] == '1' || map[ny][nx] == '4'))
				visited[i] = true;
			else if (i == 1 && (map[ny][nx] == '|' || map[ny][nx] == '+' || map[ny][nx] == '2' || map[ny][nx] == '3'))
				visited[i] = true;
			else if (i == 2 && (map[ny][nx] == '-' || map[ny][nx] == '+' || map[ny][nx] == '1' || map[ny][nx] == '2'))
				visited[i] = true;
			else if (i == 3 && (map[ny][nx] == '-' || map[ny][nx] == '+' || map[ny][nx] == '3' || map[ny][nx] == '4'))
				visited[i] = true;
		}
	}

	if (visited[0] && visited[1] && visited[2] && visited[3]) cout << "+";
	else if (visited[0] && visited[1]) cout << "|";
	else if (visited[2] && visited[3]) cout << "-";
	else if (visited[1] && visited[3]) cout << "1";
	else if (visited[0] && visited[3]) cout << "2";
	else if (visited[0] && visited[2]) cout << "3";
	else if (visited[1] && visited[2]) cout << "4";
	return;
}

void dfs(int y, int x, int d) {
	if (map[y][x] == '.') {
		result(y, x);
		return;
	}

	int ny = y + dy[d];
	int nx = x + dx[d];

	if (d == 0) { //À§
		if (map[ny][nx] == '|' || map[ny][nx] == '+') d = 0;
		else if (map[ny][nx] == '1') d = 3;
		else if (map[ny][nx] == '4') d = 2;
	}

	else if (d == 1) {	// ¾Æ·¡
		if (map[ny][nx] == '|' || map[ny][nx] == '+') d = 1;
		else if (map[ny][nx] == '2') d = 3;
		else if (map[ny][nx] == '3') d = 2;
	}

	else if (d == 2) {	// ¿Þ
		if (map[ny][nx] == '-' || map[ny][nx] == '+') d = 2;
		else if (map[ny][nx] == '1') d = 1;
		else if (map[ny][nx] == '2') d = 0;
	}

	else if (d == 3) {	// ¿À
		if (map[ny][nx] == '-' || map[ny][nx] == '+') d = 3;
		else if (map[ny][nx] == '3') d = 0;
		else if (map[ny][nx] == '4') d = 1;
	}

	dfs(ny, nx, d);
	return;
}

void check_map() {
	for (int i = 0; i < 4; i++) {
		int ny = v.front().first + dy[i];
		int nx = v.front().second + dx[i];

		if (ny <= 0 || ny > R || nx <= 0 || nx > C) continue;

		if (map[ny][nx] != '.') {
			if (ny == v.front().first) {
				if (nx == v.front().second - 1)
					dir = 2;
				else if (nx == v.front().second + 1)
					dir = 3;
			}
			else if (nx == v.front().second) {
				if (ny == v.front().first - 1)
					dir = 0;
				else if (ny == v.front().first + 1)
					dir = 1;
			}
		}
	}
}

int main() {
	cin >> R >> C;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'M')
				v.push_back(make_pair(i, j));
		}
	}

	check_map();

	dfs(v.front().first, v.front().second, dir);

	return 0;
}