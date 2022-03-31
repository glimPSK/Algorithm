/*
Q)	상근이가 모든 국가를 여행하기 위해 타야하는 비행기 최소 개수

S)	1. 국가의 수 N / 비행기 종류 M
	2. M개 줄 a,b (a-b)왕복하는 비행기

A)	1. N M 입력
	2. a,b (m개 포문)
	3. airplane[N] / 각 배열에 맞게 idx -> 연결된 선 찾기
	4. MST 알고리즘
*/

#include <iostream>
using namespace std;

int N{}, M{};

void input_data() {
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a{}, b{};
		cin >> a >> b;
	}
}

void solution() {
	// 모든 노드 연결 + 가중치 X
	// -> MST -> Node-1 = O(1)
	cout << N - 1 << endl;
}


int main() {
	int tc{};
	cin >> tc;
	for (int t = 0; t < tc; t++) {
		input_data();
		solution();
	}
	return 0;
}