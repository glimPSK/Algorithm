/*
Q)	2명의 죄수를 탈옥시키기 위해 열어야 하는 문의 개수 구해라

S)	1. H / W <= 100
	2. 빈공간 . | 벽 * | 문 # | 죄수 $

A)	1. tc -> map 입력
	2. 밖에서 들어오는 경로로 판단
*/
#include <iostream>
#include <vector>
using namespace std;

#define SIZE 110

int R{}, C{};
char map[SIZE][SIZE]{};
bool visited[SIZE][SIZE]{};

int dy[] = { 0,0,1,-1 };
int dx[] = { 1,-1,0,0 };

vector <pair<int, int>> door{};

void input_data() {
	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
			if (map[i][j] == '#') {
				door.push_back(make_pair(i, j));
				map[i][j] = '.';
			}
		}
	}
}

void solution() {
	//init
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
		}
	}
}

int main() {
	int tc{};
	cin >> tc;
	for (int t = 0; t < tc; t++) {
		input_data();
		solution();
	}
	return 0;
}