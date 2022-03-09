/*
# 3085 사탕게임.cpp
Q) 상근이가 먹을 수 있는 사탕 최대 갯수
A)	1. 사탕 색이 다른 인접한 두칸 고르기
	2. 다음 고른칸에 들어있는 사탕 서로 교환
	3. 모두 같은 색으로 이루어져 있는 가장 긴부분(행or열) 고르고 먹는다.
	(* 가장 긴부분만 1줄 먹는다.)

	각 상태마다 최대 길이가 몇인지는 알아야함 
		-> 마지막까지 다 돌려보고 최대값 판단
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
#define SIZE 52

int n{};
char map[SIZE][SIZE]{};
bool visited[SIZE][SIZE]{};

int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };

void input_data() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
}

int getMaxLength() {
	int myMax = -1;

	for (int i = 0; i < n; i++) {
		// 행 검사
		int len = 1;
		char pivot = map[i][0];
		for (int j = 1; j < n; j++) {
			if (pivot == map[i][j]) {
				len++;
			}
			else {
				pivot = map[i][j];
			}
		}
		myMax = max(myMax, len);

		// 열검사
		len = 1;
		pivot = map[0][i];
		for (int j = 1; j < n; j++) {
			if (pivot == map[j][i]) {
				len++;
			}
			else {
				pivot = map[j][i];
			}
		}
		myMax = max(myMax, len);
	}
	return myMax;
}

void solution() {
	memset(visited, false, sizeof(visited));
	int myMax = getMaxLength();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = true;
			//0,0 ~ n-1,n-1 까지 돌면서 바꾸 -> 길이판단 -> 원위치
			for (int k = 0; k < 4; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];
				if (ny < 0 || nx < 0 || ny >= n || nx >= n)	continue;
				if (!visited[ny][nx] && map[ny][nx] != map[i][j]) {
					swap(map[ny][nx], map[i][j]);
					myMax = max(myMax, getMaxLength());
					swap(map[i][j], map[ny][nx]);
				}
			}
		}
	}
	cout << myMax << endl;
}

int main() {	
	//input
	input_data();

	//solution
	solution();
	
	return 0;
}