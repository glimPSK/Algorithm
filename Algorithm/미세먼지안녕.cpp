#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

int r, c, t;
int map[64][64]{};
int result;
vector <int> air;
int dx[] = { 0,0,-1,1 };
int dy[] = { 1,-1,0,0 };


// 먼지 퍼트리기
void spreadDust() {
	int check[64][64]{};

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (map[i][j] > 0) {
				int dust = map[i][j] / 5;

				for (int k = 0; k < 4; k++) {
					int y = i + dy[k];
					int x = j + dx[k];
					if (y < 0 || x < 0 || y >= r || x >= c)	continue;
					if (map[y][x] != -1) {
						check[y][x] += dust;
						check[i][j] -= dust;
					}
				}
			}
		}
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			map[i][j] += check[i][j];
		}
	}
}
// 공기 청정
void cleaning() {
	int ar;
	vector<pair<int, int>> pts;

	//upper
	ar = air[0];
	for (int i = ar - 1; i >= 0; i--) {
		pts.push_back(make_pair(i, 0));
	}
	for (int j = 0; j < c; j++) {
		pts.push_back(make_pair(0, j));
	}
	for (int i = 0; i <= ar; i++) {
		pts.push_back(make_pair(i, c - 1));
	}
	for (int j = c - 1; j > 0; j--) {
		pts.push_back(make_pair(ar, j));
	}

	for (int i = 0; i < (signed)pts.size() - 1; i++) {
		map[pts[i].first][pts[i].second]
			= map[pts[i + 1].first][pts[i + 1].second];
	}
	map[pts[pts.size() - 1].first][pts[pts.size() - 1].second] = 0;
	pts.clear();

	//lower

	ar = air[1];
	for (int i = ar + 1; i < r; i++) {
		pts.push_back(make_pair(i, 0));
	}
	for (int j = 0; j < c; j++) {
		pts.push_back(make_pair(r - 1, j));
	}
	for (int i = r - 1; i >= ar; i--) {
		pts.push_back(make_pair(i, c - 1));
	}
	for (int j = c - 1; j >= 1; j--) {
		pts.push_back(make_pair(ar, j));
	}

	for (int i = 0; i < (signed)pts.size() - 1; i++) {
		map[pts[i].first][pts[i].second]
			= map[pts[i + 1].first][pts[i + 1].second];
	}
	map[pts[pts.size() - 1].first][pts[pts.size() - 1].second] = 0;

}
int main() {
	//input
	scanf("%d %d %d", &r, &c, &t);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == -1) {
				air.push_back(i);
			}
		}
	}
	//init
	result = 0;

	//logic
	// 공기청정기 가동
	for (int i = 0; i < t; i++) {
		spreadDust();
		cleaning();
	}
	// 청소 못한 먼지
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (map[i][j] > 0) {
				result += map[i][j];
			}
		}
	}

	//result
	printf("%d\n", result);

	return 0;
}