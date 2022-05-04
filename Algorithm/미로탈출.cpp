#define MAX 987654321
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
struct info {
	int x, y, val, wall;
};
info tmp;
int arr[1001][1001];
int check[1001][1001][2];
int row, col, sx, sy, ex, ey;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> row >> col >> sy >> sx >> ey >> ex;
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= col; j++) {
			cin >> arr[i][j];
			check[i][j][0] = MAX;
			check[i][j][1] = MAX;
		}
	queue<info> q;
	tmp.x = sx;
	tmp.y = sy;
	tmp.val = 0;
	tmp.wall = 0;
	q.push(tmp);
	check[sy][sx][0] = 0;
	int result = MAX;

	while (!q.empty()) {
		int cx = q.front().x;
		int cy = q.front().y;
		int cv = q.front().val;
		int cw = q.front().wall;
		q.pop();
		if (cx == ex && cy == ey) {
			result = cv;
			break;
		}
		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx > 0 && ny > 0 && nx <= col && ny <= row) {
				if (arr[ny][nx] == 0 && check[ny][nx][cw] > cv + 1) {		//±æ
					check[ny][nx][cw] = cv + 1;
					tmp.x = nx;
					tmp.y = ny;
					tmp.val = cv + 1;
					tmp.wall = cw;
					q.push(tmp);
				}
				else if (arr[ny][nx] == 1 && cw == 0 && check[ny][nx][1] > cv + 1) {		//º® ¶Õ±â
					check[ny][nx][1] = cv + 1;
					tmp.x = nx;
					tmp.y = ny;
					tmp.val = cv + 1;
					tmp.wall = 1;
					q.push(tmp);
				}
			}
		}
	}
	result == MAX ? cout << -1 : cout << result;
	return 0;
}