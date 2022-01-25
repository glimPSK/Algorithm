#include <iostream>
#include <vector>

using namespace std;

int main() {
	string board[3], input[6];

	auto check = [&]() -> bool {
		vector <bool> visited(6);
		int cnt = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 6; j++) {
				if (!visited[j] && board[i] == input[j]) {
					visited[j] = 1, cnt++;
					break;
				}
			}
			string temp;
			for (int j = 0; j < 3; j++) {
				temp.push_back(board[j][i]);
			}
			for (int j = 0; j < 6; j++) {
				if (!visited[j] && temp == input[j]) {
					visited[j] = 1, cnt++;
					break;
				}
			}
		}
		return cnt == 6;
	};

	for (int i = 0; i < 6; i++) cin >> input[i];
	for (int i = 0; i < 6; i++) for (int j = 0; j < 6; j++) for (int k = 0; k < 6; k++) {
		if (i == j || j == k || k == i) continue;
		board[0] = input[i];
		board[1] = input[j];
		board[2] = input[k];
		if (check()) {
			for (int i = 0; i < 3; i++) cout << board[i] << '\n';
			return 0;
		}
	}
	cout << 0 << '\n';
	return 0;
}