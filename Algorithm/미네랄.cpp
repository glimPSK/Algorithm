#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;


char cave[100][100]{};
int branch[100]{};
int N{};
int R{}, C{};
int visited[100][100];

int dy[4] = { 1,-1,0,0 };
int dx[4] = { 0,0,1,-1 };

vector<pair<int, int>> group;

void dfs(int y, int x) {
	if (cave[y][x] == '.') return;
	if (visited[y][x]) return;

	visited[y][x] = true;
	group.push_back({ y,x });

	for (int i = 0; i < 4; ++i) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (0 <= nx && nx < C && 0 <= ny && ny < R) dfs(ny, nx);
	}
}

void solve() {
	memset(visited, 0, sizeof(visited));
	
	for (int a = 0; a < R; ++a) {
		for (int b = 0; b < C; ++b) {
			if (visited[a][b]) continue;
			if (cave[a][b] == '.') continue;

			group.clear();
			dfs(a, b);
			vector<int> low(C, -1);

			for (int i = 0; i < group.size(); ++i) {
				auto& p = group[i];
				//각 열마다 가장 밑에있는 행을 찾는다
				low[p.second] = max(low[p.second], p.first);
				//옮길점들 이므로 '.'로 바꿔주자
				cave[p.first][p.second] = '.';
			}

			//얼마나 밑으로 옮길지 결정
			int lowmove = R;
			for (int i, j = 0; j < C; ++j) {
				if (low[j] == -1) continue;
				i = low[j];

				// 내려갈수 있을때까지 내려간다
				while (i < R && cave[i][j] == '.') {
					++i;
				}
				lowmove = min(lowmove, i - low[j] - 1);
			}

			for (int i = 0; i < group.size(); ++i) {
				auto& p = group[i];
				p.first += lowmove;
				cave[p.first][p.second] = 'x';
				visited[p.first][p.second] = true;
			}
		}
	}
}

int main() {
	//input data
	cin >> R >> C;
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j)	{
			cin >> cave[i][j];
		}
	}

	cin >> N;
	for (int i = 0; i < N; ++i) {
		int num;
		cin >> num;
		branch[i] = R - num;
	}

	// 한번 맞치고 한번 dfs 검사
	for (int i = 0; i < N; ++i){
		int height = branch[i];
		if (i % 2 == 0) {
			for (int j = 0; j < C; ++j)	{
				if (cave[height][j] == 'x') {
					cave[height][j] = '.';
					break;
				}
			}
		}
		else {
			for (int j = C - 1; j >= 0; --j) {
				if (cave[height][j] == 'x') {
					cave[height][j] = '.';
					break;
				}
			}
		}
		// dfs 검사
		solve();
	}

	// result
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j)
			cout << cave[i][j];
		cout << "\n";
	}

	return 0;
}