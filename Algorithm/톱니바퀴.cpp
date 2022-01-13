#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

int tobni[4][8]{};
int k, n, d;
int res;

void updateTobni(int x, int dir) {
	int temp{};
	if (dir == 1) {
		temp = tobni[x][7];
		for (int i = 6; i >= 0; i--) {
			tobni[x][i + 1] = tobni[x][i];
		}
		tobni[x][0] = temp;
	}
	else {
		temp = tobni[x][0];
		for (int i = 0; i < 7; i++) {
			tobni[x][i] = tobni[x][i + 1];
		}
		tobni[x][7] = temp;
	}
}

void rotate() {
	for (int t = 0; t < k; t++) {
		scanf("%d %d", &n, &d);

		int direct[4]{};
		direct[n - 1] = d;

		for (int i = n - 1; i < 3; i++) {
			if (tobni[i][2] != tobni[i + 1][6]) direct[i + 1] = -direct[i];
		}
		for (int i = n - 1; i > 0; i--) {
			if (tobni[i][6] != tobni[i - 1][2]) direct[i - 1] = -direct[i];
		}

		for (int i = 0; i < 4; i++) {
			if (direct[i]) {
				updateTobni(i, direct[i]);
			}
		}
	}
}

int main() {
	//input
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			scanf("%1d", &tobni[i][j]);
		}
	}
	scanf("%d", &k);
	rotate();

	// result
	for (int i = 0; i < 4; i++) {
		if (tobni[i][0]) res += (1 << i);
	}
	printf("%d", res);
	return 0;
}