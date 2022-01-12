/*
# Q
- 스타트 팀과 링크 팀의 능력치의 차이를 최소값은?

# Aglo
- 2개의 팀으로 나눈다
- n/2 개의 수와 일치할 때 -> 팀차이 계산
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 987987987

int map[25][25];
int n;
int myMin;
int c[25];

void dfs(int player, int x) {
	if (x == n / 2) {
		vector<int> sTeam, lTeam;
		for (int i = 0; i < n; i++) {
			if (c[i]) sTeam.push_back(i);
			else lTeam.push_back(i);
		}
		int sSum = 0;
		int lSum = 0;
		for (int i = 0; i < sTeam.size(); i++) {
			for (int j = i + 1; j < sTeam.size(); j++) {
				int sX = sTeam[i];
				int sY = sTeam[j];
				int lX = lTeam[i];
				int lY = lTeam[j];

				sSum += map[sY][sX] + map[sX][sY];
				lSum += map[lY][lX] + map[lX][lY];
			}
		}
		myMin = min(myMin, abs(sSum - lSum));
		return;
	}
	for (int i = player + 1; i < n; i++) {
		if (c[i] == 0) {
			c[i] = 1;
			dfs(i, x + 1);
			c[i] = 0;
		}
	}
}

int main() {
	//init
	myMin = MAX;

	//input
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	//logic
	dfs(0, 0);

	//result
	printf("%d\n", myMin);
	return 0;
}