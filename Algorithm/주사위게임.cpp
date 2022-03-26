/*
Q)	몇번만에 도착하는지?

S)	1. 출발점 1칸 / 도착점 N칸
	2. 지시사항 - 말을 얼만큼 이동해야 하는지
	3. N칸 도착 및 N칸 넘어서면 도착
	4. 주사위 눈만큼 이동 -> 지시에 따름 -> 도착(지시사항 보지 않음)

A)	1. N M 입력
	2. N 개 for 문 -> 맵입력
	3. M 개 for 문 -> 주사위 입력
	4. S-4번을 따른다. 
*/

#include <iostream>
using namespace std;
#define SIZE 1010

int n{}, m{};
int map[SIZE]{};
int dice[SIZE]{};

int nIdx{};

void input_data() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> map[i];
	}
	for (int i = 1; i <= m; i++) {
		cin >> dice[i];
	}
}

void solution() {
	//init
	nIdx = 1;

	for (int i = 1; i <= m; i++) {
		// 눈만큼 이동
		nIdx += dice[i];
		if (nIdx >= n) {
			cout << i << endl;
			return;
		}
		// 지시에 따름 -> 도착
		nIdx += map[nIdx];
		if (nIdx <= 1)	nIdx = 1;
		if (nIdx >= n) {
			cout << i << endl;
			return;
		}
	}
}

int main() {
	input_data();
	solution();
	return 0;
}