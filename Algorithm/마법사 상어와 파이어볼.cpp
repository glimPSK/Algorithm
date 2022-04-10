#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

#define SIZE 52

struct INFO {
	int y{};
	int x{};
	int m{};
	int s{};
	int d{};
};

int n{}, m{}, k{};
vector <INFO> ball{};
vector <int> map[SIZE][SIZE];

int dy[] = { -1,-1,0,1,1,1,0,-1 };
int dx[] = { 0,1,1,1,0,-1,-1,-1 };

void move() {
	vector <int> nMap[SIZE][SIZE]{};
	for (int i = 0; i < ball.size(); i++) {
		int nd = ball[i].d;
		int ns = ball[i].s % n;
		int ny = (ball[i].y + (dy[nd] * ns) + n) % n;
		int nx = (ball[i].x + (dx[nd] * ns) + n) % n;
		nMap[ny][nx].push_back(i);
		ball[i].y = ny;
		ball[i].x = nx;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			map[i][j] = nMap[i][j];
		}
	}
}

void sum() {
	vector <INFO> nBall{};

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j].size() == 0)	continue;
			if (map[i][j].size() == 1) {
				int idx = map[i][j][0];
				nBall.push_back(ball[idx]);
				continue;
			}
			int sm = 0;
			int ss = 0;
			bool add = true;
			bool even = true;
			for (int k = 0; k < map[i][j].size(); k++) {
				int idx = map[i][j][k];
				sm += ball[idx].m;
				ss += ball[idx].s;
				if (ball[idx].d % 2 == 0) {
					add = false;
				}
				else {
					even = false;
				}
			}

			if (sm / 5 == 0) continue;

			int cm = sm / 5;
			int cs = ss / map[i][j].size();

			for (int k = 0; k < 4; k++) {
				if (add || even) {
					nBall.push_back({ i,j,cm,cs,k * 2 });
				}
				else {
					nBall.push_back({ i,j,cm,cs,k * 2 + 1 });
				}
			}
		}
	}

	ball = nBall;
}


int getResult() {
	int sum = 0;
	for (int i = 0; i < ball.size(); i++) {
		sum += ball[i].m;
	}
	return sum;
}

void input_data() {
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++) {
		int y{}, x{}, m{}, s{}, d{};
		cin >> y >> x >> m >> s >> d;
		//init
		map[y - 1][x - 1].push_back(i);
		ball.push_back({ y - 1,x - 1,m,s,d });
	}
}

void solution() {
	/*
	1. 모든 파이어볼이 자신의 방향 di로 속력 si칸 만큼 이동한다.
		1. 이동하는 중에는 같은 칸에 여러 개의 파이어볼이 있을 수도 있다.
	2. 이동이 모두 끝난 뒤, 2개 이상의 파이어볼이 있는 칸에서는 다음과 같은 일이 일어난다.
		1.같은 칸에 있는 파이어볼은 모두 하나로 합쳐진다.
		2.파이어볼은 4개의 파이어볼로 나누어진다.
		3.나누어진 파이어볼의 질량, 속력, 방향은 다음과 같다.
			1)질량은 ⌊(합쳐진 파이어볼 질량의 합)/5⌋이다.
			2)속력은 ⌊(합쳐진 파이어볼 속력의 합)/(합쳐진 파이어볼의 개수)⌋이다.
			3)합쳐지는 파이어볼의 방향이 모두 홀수이거나 모두 짝수이면, 방향은 0, 2, 4, 6이 되고, 그렇지 않으면 1, 3, 5, 7이 된다.
		4.질량이 0인 파이어볼은 소멸되어 없어진다.
	*/
	for (int t = 0; t < k; t++) {
		move();
		sum();
	}
	//result
	int nRes = getResult();
	cout << nRes << endl;
}

int main() {
	input_data();
	solution();
	return 0;
}