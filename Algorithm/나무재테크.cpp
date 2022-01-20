#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int SIZE = 16;

vector<int> tree[SIZE][SIZE]{};

int n, m, k;
int add[SIZE][SIZE];
int nut[SIZE][SIZE];
int map[SIZE][SIZE];

int dy[] = { -1,-1,-1,0,0,1,1,1 };
int dx[] = { -1,0,1,-1,1,-1,0,1 };

void spring_summer() {
	// 봄 여름
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sort(tree[i][j].begin(), tree[i][j].end());

			int dNut = 0;
			vector<int> temp{};
			for (int k = 0; k < tree[i][j].size(); k++) {
				if (nut[i][j] >= tree[i][j][k]) {
					temp.push_back(tree[i][j][k] + 1);
					nut[i][j] -= tree[i][j][k];
				}
				else {
					dNut += tree[i][j][k] / 2;
				}
			}
			nut[i][j] += dNut;
			tree[i][j] = temp;
		}
	}
}

void fall() {
	memset(map, 0, sizeof(map));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < tree[i][j].size(); ++k) {
				if (tree[i][j][k] % 5 == 0) {
					for (int next = 0; next < 8; ++next)
					{
						int ny = i + dy[next];
						int nx = j + dx[next];
						if (!(0 <= ny && ny < n && 0 <= nx && nx < n)) continue;
						map[ny][nx] += 1;
					}
				}
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < map[i][j]; ++k)
				tree[i][j].push_back(1);
		}
	}
}

void winter() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			nut[i][j] += add[i][j];
		}
	}
}


int main() {
	//Input data
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			//init nut
			nut[i][j] = 5;
			scanf("%d", &add[i][j]);
		}
	}
	for (int i = 0; i < m; i++) {
		int y, x, age;
		scanf("%d %d %d", &y, &x, &age);
		tree[y - 1][x - 1].push_back(age);
	}

	//Logic
	for (int i = 0; i < k; i++) {
		spring_summer();
		//가을
		fall();
		//겨울
		winter();
	}

	//Result
	int nRes = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
		{
			nRes += tree[i][j].size();
		}
	}
	printf("%d\n", nRes);

	return 0;
}