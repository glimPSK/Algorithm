#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 987987987;
const int MAX = 64;

vector <pair<int, int>> home{};
vector <pair<int, int>> fried{};

int n{}, m{};
int map[64][64]{};
bool v[16]{};
int nRes{};


int getDistance(pair<int, int> h, pair<int, int> s) {
	return abs(h.first - s.first) + abs(h.second - s.second);
}

void dfs(int idx, int x) {
	int homeSize = home.size();
	int friedSize = fried.size();

	if (idx > friedSize)	return;

	if (x == m) {
		int sum = 0;
		for (int i = 0; i < homeSize; i++) {
			int data = INF;

			for (int j = 0; j < friedSize; j++) {
				if (v[j]) {
					data = min(data, getDistance(home[i], fried[j]));
				}
			}
			sum += data;
		}
		nRes = min(nRes, sum);
		return;
	}
	v[idx] = true;
	dfs(idx + 1, x + 1);
	v[idx] = false;
	dfs(idx + 1, x);
}

int main() {
	// Input Data
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1) home.push_back({ i,j });
			else if (map[i][j] == 2) fried.push_back({ i,j });
		}
	}
	// Init
	nRes = INF;

	// Logic
	dfs(0, 0);

	// Result
	printf("%d\n", nRes);
	return 0;
}