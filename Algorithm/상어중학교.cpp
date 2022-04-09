#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int SIZE = 20;
const int INF = 987654321;
const int MAX = 20;
const int EMPTY = -2;
const int BLACK = -1;
const int RAINBOW = 0;

typedef struct {
	int y, x;
} S_POS;

typedef struct {
	S_POS baseBlock;
	S_POS arr[MAX * MAX];
	int blockGroupSize;
	int rainbowCnt;
} S_BLACK;

int N{}, M{};
int board[MAX][MAX];
bool visited[MAX][MAX];

int dy[] = { 0,0,1,-1 };
int dx[] = { 1,-1,0,0 };

void input_data() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
}

void gravity() {
	// 중력
	for (int i = N - 2; i >= 0; i--) { 
		for (int j = 0; j < N; j++)	{
			if (board[i][j] <= BLACK) {
				continue;
			}

			int y = i;

			while (true) {
				if (y == N)	{
					break;
				}

				int cur = board[y][j];
				int next = board[y + 1][j];

				if (next != EMPTY) {
					break;
				}

				board[y + 1][j] = cur;
				board[y][j] = EMPTY;
				y++;
			}
		}
	}
}

void rotateBoard() {
	int tempBoard[MAX][MAX];

	for (int i = 0; i < N; i++)	{
		for (int j = 0; j < N; j++) {
			tempBoard[i][j] = board[i][j];
		}
	}

	for (int i = 0; i < N; i++)	{
		for (int j = 0; j < N; j++) {
			board[N - (j + 1)][i] = tempBoard[i][j];
		}
	}
}

S_BLACK getS_BLACK(int y, int x, int color) {
	S_BLACK tempS_BLACK;
	tempS_BLACK.baseBlock = { INF, INF };
	tempS_BLACK.rainbowCnt = 0;

	int baseColor = board[y][x] == RAINBOW ? color : board[y][x];

	int tempBoard[MAX][MAX];

	for (int i = 0; i < N; i++)	{
		for (int j = 0; j < N; j++)	{
			tempBoard[i][j] = board[i][j] == RAINBOW ? color : board[i][j];
		}
	}

	queue<S_POS> q;
	q.push({ y, x });
	visited[y][x] = true;
	int arrIdx = 0;

	while (!q.empty()) {
		int curY = q.front().y;
		int curX = q.front().x;
		q.pop();

		// 무지개블록 수
		if (board[curY][curX] == RAINBOW)
		{
			tempS_BLACK.rainbowCnt++;
		}

		// 기준 블록은 무지개 블록이 아닌 블록 중에서 행의 번호가 가장 작은 블록,
		// 그러한 블록이 여러개면 열의 번호가 가장 작은 블록이다.
		if (board[curY][curX] != RAINBOW
			&& (tempS_BLACK.baseBlock.y > curY
				|| (tempS_BLACK.baseBlock.y == curY && tempS_BLACK.baseBlock.x > curX)))
		{
			tempS_BLACK.baseBlock = { curY, curX };
		}

		// 블록을 그룹에 추가
		tempS_BLACK.arr[arrIdx++] = { curY, curX };

		for (int k = 0; k < 4; k++) {
			int nextY = curY + dy[k];
			int nextX = curX + dx[k];

			if (nextY < 0 || nextY >= N || nextX < 0 || nextX >= N || tempBoard[nextY][nextX] <= BLACK) continue;
			// 같은 색깔이 아니라면
			if (tempBoard[nextY][nextX] != baseColor) continue;
			if (visited[nextY][nextX]) continue;

			visited[nextY][nextX] = true;
			q.push({ nextY, nextX });
		}
	}

	tempS_BLACK.blockGroupSize = arrIdx;
	if (tempS_BLACK.rainbowCnt == arrIdx) {
		tempS_BLACK.blockGroupSize = 0;
	}

	return tempS_BLACK;
}

int getScore() {
	S_BLACK blockGroup;
	blockGroup.rainbowCnt = 0;
	blockGroup.blockGroupSize = 0;
	blockGroup.baseBlock = { INF, INF };

	for (int y = 0; y < N; y++)	{
		for (int x = 0; x < N; x++)	{
			if (board[y][x] <= BLACK) {
				continue;
			}

			// 무지개 블록을 각 색깔마다 지정하여 진행
			for (int color = 1; color <= M; color++) {
				memset(visited, false, sizeof(visited));

				S_BLACK tempS_BLACK = getS_BLACK(y, x, color);

				if (tempS_BLACK.blockGroupSize < 2) {
					continue;
				}

				// 크기가 가장 큰 블록 그룹을 찾는다
				if (tempS_BLACK.blockGroupSize > blockGroup.blockGroupSize) {
					blockGroup = tempS_BLACK;

					continue;
				}

				// 그러한 블록 그룹이 여러 개라면 포함된 무지개 블록의 수가 가장 많은 블록 그룹
				if (tempS_BLACK.blockGroupSize == blockGroup.blockGroupSize)	{
					if (tempS_BLACK.rainbowCnt > blockGroup.rainbowCnt) {
						blockGroup = tempS_BLACK;

						continue;
					}

					// 그러한 블록도 여러개라면 기준 블록의 행이 가장 큰 것을, 그 것도 여러개이면 열이 가장 큰 것을 찾는다
					if (tempS_BLACK.rainbowCnt == blockGroup.rainbowCnt)	{
						if (blockGroup.baseBlock.y < tempS_BLACK.baseBlock.y
							|| (blockGroup.baseBlock.y == tempS_BLACK.baseBlock.y
								&& blockGroup.baseBlock.x < tempS_BLACK.baseBlock.x)) {
							blockGroup = tempS_BLACK;
						}
					}
				}
			}
		}
	}

	// 그룹에 속한 블록의 개수는 2보다 크거나 같아야하며
	if (blockGroup.blockGroupSize < 2) return 0;

	for (int i = 0; i < blockGroup.blockGroupSize; i++) {
		board[blockGroup.arr[i].y][blockGroup.arr[i].x] = EMPTY;
	}
	return blockGroup.blockGroupSize * blockGroup.blockGroupSize;
}

void solution() {
	/*
	1) 크기가 가장 큰 블록 그룹을 찾는다. 
		그러한 블록 그룹이 여러 개라면 포함된 무지개 블록의 수가 가장 많은 블록 그룹, 
		그러한 블록도 여러개라면 기준 블록의 행이 가장 큰 것을, 그 것도 여러개이면 열이 가장 큰 것을 찾는다.
	2) 1에서 찾은 블록 그룹의 모든 블록을 제거한다. 
		블록 그룹에 포함된 블록의 수를 B라고 했을 때, B2점을 획득한다.
	3) 격자에 중력이 작용한다.
	4) 격자가 90도 반시계 방향으로 회전한다.
	5) 다시 격자에 중력이 작용한다.
	*/
	int result = 0;
	while (true) {
		int score = getScore();
		if (score == 0)	break;
		result += score;
		gravity();
		rotateBoard();
		gravity();
	}

	cout << result << "\n";
}

int main() {
	input_data();
	solution();
	return 0;
}