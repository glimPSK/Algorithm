#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

#define SIZE 1505

int R{}, C{};
string lake[SIZE];
bool visited[SIZE][SIZE]{};

vector <pair<int, int>> swan{};
queue <pair<int, int>> water{};
queue<pair<int, int>> q{};

int dy[] = { 0,0,1,-1 };
int dx[] = { 1,-1,0,0 };

void solution() {
	q.push(swan[0]);

	visited[swan[0].first][swan[0].second] = true;

	int day = 0;

	while (true) {
		queue<pair<int, int>> next_q{};
		bool flag = false;
		while (!q.empty()) {
			int y = q.front().first;
			int x = q.front().second;
			q.pop();

			if (y == swan[1].first && x == swan[1].second) {
				flag = true;
				break;
			}

			for (int i = 0; i < 4; i++) {
				int nextY = y + dy[i];
				int nextX = x + dx[i];

				if (nextY < 0 || nextY >= R || nextX < 0 || nextX >= C || visited[nextY][nextX]) continue;

				visited[nextY][nextX] = true;

				// 물에 인접한 얼음이므로 다음 날에 백조가 탐색할 곳이므로 nextQ에 넣어준다
				if (lake[nextY][nextX] == 'X') {
					next_q.push({ nextY, nextX });
					continue;
				}

				q.push({ nextY, nextX });
			}
		}

		if (flag)
			break;

		q = next_q;

		// 얼음을 녹이는 과정
		size_t waterSize = water.size();
		while (waterSize--)
		{
			int y = water.front().first;
			int x = water.front().second;
			water.pop();

			for (int i = 0; i < 4; i++)
			{
				int nextY = y + dy[i];
				int nextX = x + dx[i];

				if (nextY < 0 || nextY >= R || nextX < 0 || nextX >= C)
				{
					continue;
				}

				if (lake[nextY][nextX] == 'X')
				{
					lake[nextY][nextX] = '.';
					water.push({ nextY, nextX });
				}
			}
		}

		day++;
	}
	//result
	cout << day << "\n";
}

void input_data() {
	cin >> R >> C;

	for (int i = 0; i < R; i++) {
		cin >> lake[i];

		for (int j = 0; j < C; j++) {
			if (lake[i][j] == 'L') {
				swan.push_back({ i, j });
			}
			if (lake[i][j] == '.' || lake[i][j] == 'L') {
				water.push({ i, j });
			}
		}
	}
}

int main(void) {
	input_data();
	solution();
	return 0;
}