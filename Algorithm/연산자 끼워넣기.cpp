#include <iostream>
#include <algorithm>
using namespace std;

#define INF 1000000000
#define SIZE 12

int n{};
int arr[SIZE]{};
int booho[4]{};
int myMax{};
int myMin{};

void input_data() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	for (int i = 0; i < 4; i++) {
		cin >> booho[i];
	}
}

void dfs(int idx, int res) {
	// 다음 숫자가 없으면 끝
	if (idx == n) {
		// 최대값 최소값 갱신
		myMax = max(myMax, res);
		myMin = min(myMin, res);
		return;
	}


	//개수만큼 반복
	for (int k = 0; k < 4; k++) {
		if (booho[k] > 0) {
			booho[k]--;
			if (k == 0) {
				dfs(idx + 1, res + arr[idx]);
			}
			else if (k == 1) {
				dfs(idx + 1, res - arr[idx]);
			}
			else if (k == 2) {
				dfs(idx + 1, res * arr[idx]);
			}
			else if (k == 3) {
				dfs(idx + 1, res / arr[idx]);
			}
			booho[k]++;
		}
	}
}

void solution() {
	//init
	myMax = -INF;
	myMin = INF;

	//logic
	dfs(1, arr[0]);

	//result
	cout << myMax << endl;
	cout << myMin << endl;
}

int main() {
	//input
	input_data();

	//solve
	solution();

	return 0;
}