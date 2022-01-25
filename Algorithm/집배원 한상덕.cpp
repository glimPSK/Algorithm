
/*
- 3s / 256 MB
- 우체국 : P / 집 : K / 목초지 : .
- 배달 P에서 시작 수평, 수직, 대각선 인접한 칸이동가능
- 배달 후 -> 우체국으로 돌아와야 한다.
- (높은곳 - 낮은곳) => 피로도 
- 가장 작은 피로도로 모든 집에 배달하려면??
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#define SIZE 52

int n{};
char map[SIZE][SIZE]{};
int high[SIZE][SIZE]{};

int px{}, py{};
int dy[] = { -1,-1,-1,0,1,1,1,0 };
int dx[] = { -1,0,1,1,1,0,-1,-1 };
int cnt{};

void input_data() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf(" %c", &map[i][j]);
			if (map[i][j] == 'K')	cnt++;
			else if (map[i][j] == 'P') {
				py = i;
				px = j;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &high[i][j]);
		}
	}
}

int solution() {
	// 모든 루트를 다 가보면서 피로도가 낮도록 계산 후 갱신

	return 0;
}

int main() {
	//init
	cnt = 0;

	//input
	input_data();

	//solve
	int nRes = solution();

	//result
	printf("%d\n", nRes);
	
	return 0;
}