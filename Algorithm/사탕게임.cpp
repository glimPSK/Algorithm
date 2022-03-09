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
#include <string>
using namespace std;
#define SIZE 52

int n{};
char map[SIZE][SIZE]{};
bool visited[SIZE][SIZE]{};

void input_data() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
}

int getMaxLength() {
	int maxLen = 1;
	// 좌우 
	for (int i = 0; i < n; i++)	{
		int len = 1;
		for (int j = 1; j < n; j++)
			if (map[i][j - 1] == map[i][j])
				len++;
			else {
				maxLen = max(maxLen, len);
				len = 1;
			}
		maxLen = max(maxLen, len);
	}
	// 상하
	for (int i = 0; i < n; i++)	{
		int len = 1;
		for (int j = 0; j < n - 1; j++)
			if (map[j + 1][i] == map[j][i])
				len++;
			else {
				maxLen = max(maxLen, len);
				len = 1;
			}
		maxLen = max(maxLen, len);
	}

	return maxLen;
}

void solution() {
	int myMax = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			//양 옆 swap
			swap(map[i][j], map[i][j + 1]);
			myMax = max(myMax, getMaxLength());
			swap(map[i][j], map[i][j + 1]);
			//위 아래 swap
			swap(map[j][i], map[j + 1][i]);
			myMax = max(myMax, getMaxLength());
			swap(map[j][i], map[j + 1][i]);
		}
	}
	//result
	cout << myMax << "\n";
}

int main() {	
	//input
	input_data();

	//solution
	solution();
	
	return 0;
}