/*
Q)	지훈이가 불에 타기전에 탈출할 수 있는 지 여부
	+ 얼마나 빨리 탈출할 수 있을지?

S)	1. 벽# / 공간. / 초기위치J/  불 F
	2. 지훈,불 -> 상하좌우로만 움직임
	4. 불은 4방향 모두로 확산됨
	5. 지훈이가 미로 가장자리에 접하면 탈출

A)	1. 맵 -> queue에 불 담기
	2. 불 시간 탐색 -> bfs
	3. 지훈이가 탈출 -> bfs 
*/
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

#define SIZE 1005

int R{}, C{};
string map[SIZE]{};
bool visited[SIZE][SIZE]{};

pair<int, int> start{};
vector<pair<int, int>> fire{};

int dy[] = { 0,0,1,-1 };
int dx[] = { 1,-1,0,0 };

int bfs() { 
    queue<pair<int, int>> q{};
    queue<pair<int, int>> flame{};

    q.push(start);

    for (int i = 0; i < fire.size(); i++){

        flame.push(fire[i]);
    }
    int result = 0;

    while (!q.empty()) {
        //불
        size_t flameSize = flame.size();
        for (int i = 0; i < flameSize; i++) {
            int y = flame.front().first;
            int x = flame.front().second;
            flame.pop();

            for (int i = 0; i < 4; i++) {
                int ny = y + dy[i];
                int nx = x + dx[i];

                if (0 <= ny && ny < R && 0 <= nx && nx < C) {
                    if (map[ny][nx] == '.' || map[ny][nx] == 'J') {
                        map[ny][nx] = 'F';
                        flame.push({ ny, nx });
                    }
                }
            }
        }

        //지훈
        size_t curSize = q.size();
        for (int i = 0; i < curSize; i++) {
            int y = q.front().first;
            int x = q.front().second;
            q.pop();

            //끝자락에 있을 경우
            if (y == 0 || y == R - 1 || x == 0 || x == C - 1) {
                return result + 1;
            }

            for (int i = 0; i < 4; i++) {
                int ny = y + dy[i];
                int nx = x + dx[i];

                if (0 <= ny && ny < R && 0 <= nx && nx < C && !visited[ny][nx]) {
                    if (map[ny][nx] == '.') {
                        visited[ny][nx] = true;
                        q.push({ ny, nx });
                    }
                }
            }
        }
        result++;
    }
    return -1;
}

void input_data() {
    cin >> R >> C;
    for (int i = 0; i < R; i++) {
        cin >> map[i];
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 'J')  start = { i, j };
            else if (map[i][j] == 'F') fire.push_back({ i, j });
        }
    }
}

void solution() {
    int result = bfs();
    if (result == -1) {
        cout << "IMPOSSIBLE" << endl;
    }
    else {
        cout << result << endl;
    }
}


int main(void) {
    input_data();
    solution();
    return 0;
}