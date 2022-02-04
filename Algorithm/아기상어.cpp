#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define SIZE 25
#define MIN 987987987

int n{};
int map[SIZE][SIZE]{};
int nRes{};

int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };

int sY{}, sX{}, sSize{};	// shark info
int cnt{}, dis{};

vector < pair <pair<int, int>, int >> fish{};

void bfs(int y, int x) {
	int v[SIZE][SIZE]{};

	dis = MIN;
	fish.clear();

	queue <pair<int, int>> Q;
	Q.push(make_pair(y, x));

	while (!Q.empty()) {
		int y = Q.front().first;
		int x = Q.front().second;
		Q.pop();

		for (int k = 0; k < 4; k++) {
			int nX = x + dx[k];
			int nY = y + dy[k];
			if (nY < 0 || nX < 0 || nY >= n || nX >= n) continue;
			if (!v[nY][nX] && sSize >= map[nY][nX]) {
				v[nY][nX] = v[y][x] + 1;
				Q.push(make_pair(nY, nX));
				if (map[nY][nX] > 0 && map[nY][nX] < sSize) {
					if (dis >= v[nY][nX]) {
						dis = v[nY][nX];
						fish.push_back(make_pair(make_pair(nY, nX), dis));
					}
				}
			}
		}
	}
}

int main() {
	// Input Data
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);

			// Init
			if (map[i][j] == 9) {
				map[i][j] = 0;
				sY = i;
				sX = j;
				sSize = 2;
			}
		}
	}

	// Logic
	while (true) {
		bfs(sY, sX);

		if (fish.empty())	break;
		sort(fish.begin(), fish.end());
		cnt++;
		nRes += fish[0].second;
		map[fish[0].first.first][fish[0].first.second] = 0;

		sY = fish[0].first.first;
		sX = fish[0].first.second;

		if (sSize == cnt) {
			sSize++;
			cnt = 0;
		}
	}

	// Result
	printf("%d\n", nRes);
	return 0;
}