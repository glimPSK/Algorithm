/*
# 3184 양 

Q)	아침이 도달했을 때 살아남은 양과 늑대의 수 출력

S)	1. # 울타리 / o 양 / v 늑대
	2. 수평 수직으로만 이동
	3. 울타리를 지나지 않고 다른칸으로 이동할 수 있다면 -> 같은영역
	4. 양 수 > 늑대 수 (양이 이김) otherwise, 영역안 양 모두 잡아먹힘

A)	1. 입력 시 양, 늑대 수 
	2. 마당 전부 탐색 -> 양or늑대 -> BFS
	3. 울타리 안 영역에서 양, 늑대 수 count
		3-1) 양 > 늑대 -> 늑대 사망
		3-2) 양 < 늑대 -> 양 사망
	4. 양, 늑대 출력
*/
#include <iostream>
#include <queue>
#include <string>
using namespace std;

const int MAX = 250;

int R{}, C{};
int sheep{}, wolf{};
string map[MAX]{};
bool visited[MAX][MAX]{};

int dy[] = { 0,0,1,-1 };
int dx[] = { 1,-1,0,0 };

void BFS(int my, int mx) {
    int curSheep{}, curWolf{};
    queue <pair<int, int>> Q;

    Q.push({ my, mx });
    visited[my][mx] = true;

    if (map[my][mx] == 'o')   curSheep++;
    else if (map[my][mx] == 'v')  curWolf++;

    //같은 칸 안에 있는 양과 늑대의 수를 센다
    while (!Q.empty()) {
        int y = Q.front().first;
        int x = Q.front().second;
        Q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (ny < 0 || nx < 0 || ny >= R || nx >= C) continue;
            if(!visited[ny][nx] && map[ny][nx] != '#') {
                visited[ny][nx] = true;
                if (map[ny][nx] == 'o') curSheep++;
                else if (map[ny][nx] == 'v')    curWolf++;
                Q.push({ ny, nx });
            }
        }
    }

    //양이 더 많으면 늑대가 죽고
    if (curSheep > curWolf) wolf -= curWolf;
    //양이 적거나 같으면 양이 죽는다
    else    sheep -= curSheep;
}

void input_data() {
    cin >> R >> C;

    for (int i = 0; i < R; i++) {
        cin >> map[i];
        for (int j = 0; j < C; j++)
            if (map[i][j] == 'o')
                sheep++;
            else if (map[i][j] == 'v')
                wolf++;
    }
}

void solution() {
    //logic
    //아직 방문하지 않은 칸이고 양이나 늑대일 때 BFS 호출
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if ((map[i][j] == 'o' || map[i][j] == 'v') && !visited[i][j]) {
                BFS(i, j);
            }
        }
    }
    //result
    cout << sheep << " " << wolf << "\n";
}

int main(void) {
    input_data();

    solution();

    return 0;
}