#include <iostream>
#include <vector>
using namespace std;

int N{};
int cnt{};

vector<vector<int>> map{};

// 움직이는 모래의 정도
double p[9] = { 0.05, 0.1, 0.1, 0.02, 0.02, 0.07, 0.07, 0.01, 0.01 };

// 좌 하 우 상
int dy[] = { 0,1,0,-1 };
int dx[] = { -1, 0,1,0 };

int m_dy[4][10] = {
	{0,-1,1, -2,2,-1,1,-1,1,0},
	{2,1,1,0,0,0,0,-1,-1,1},
	{0,-1,1, -2,2,-1,1,-1,1,0},
	{-2,-1,-1,0,0,0,0,1,1,-1}
};
int m_dx[4][10] = {
	{-2,-1,-1,0,0,0,0,1,1,-1},
	{0,-1,1, -2,2,-1,1,-1,1,0},
	{2,1,1,0,0,0,0,-1,-1,1},
	{0,-1,1, -2,2,-1,1,-1,1,0}
};

int spread() {
	int y = N / 2;
	int x = N / 2;
	int dist = 1;
	int d = 0; // 방향 정보 ( 0 : 좌, 1 : 하, 2 : 우, 3 : 상)
	int cnt = 0;
	int nRes = 0;

	while (true) {
		cnt++;
		for (int m = 0; m < dist; m++) {
			int ny = y + dy[d];
			int nx = x + dx[d];
			y = ny;
			x = nx;

			int sand = map[ny][nx];
			for (int k = 0; k < 9; k++) {
				int m_ny = ny + m_dy[d][k];
				int m_nx = nx + m_dx[d][k];
				int m_sand = (int)(map[ny][nx] * p[k]);
				sand -= m_sand;
				if (m_ny < 0 || m_ny >= N || m_nx < 0 || m_nx >= N) {
					nRes += m_sand;
				}
				else {
					map[m_ny][m_nx] += m_sand;
				}
			}
			//나머지 모래 이동
			int m_ny = ny + m_dy[d][9];
			int m_nx = nx + m_dx[d][9];
			if (m_ny < 0 || m_ny >= N || m_nx < 0 || m_nx >= N) {
				nRes += sand;
			}
			else
				map[m_ny][m_nx] += sand;

			map[ny][nx] = 0;
			if (ny == 0 && nx == 0)
				return nRes;
		}
		if (cnt == 2) {
			dist++;
			cnt = 0;
		}
		d = (d + 1) % 4;
	}
	return nRes;
}

void input_data() {
	cin >> N;
	map = vector<vector<int>>(N, vector<int>(N, 0));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
}

void solution() {
	int nRes = spread();
	cout << nRes;
}
int main() {
	input_data();
	solution();
	return 0;
}