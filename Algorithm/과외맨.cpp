/*
Q)	가장 짧은 경로의 길이 출력(타일의 개수)

S)	1. 첫번째 줄의 타일 번호 : 1 / 마지막 타일 번호 : N
	2. 두번쨰 줄에서 첫타일의 번호 N+1 / 마지막 2 * N - 1 

A)	1. 입력
	2. BFS
*/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define SIZE 501

struct S_TILE {
    int value;
    int num;
    int dist;
};
S_TILE map[SIZE][SIZE * 2]{};
int path[SIZE * SIZE]{};
int N{};

int dr[4] = { 0,0,-1,1 };
int dc[4] = { -1,1,0,0 };

vector<int> way{};
int last = 1;

void bfs() {
    queue<pair<int, int>> q{};
    
    //init
    q.push({ 1,1 });
    q.push({ 1,2 });
    map[1][1].dist = 1;
    map[1][2].dist = 1;
    
    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            int col = nr % 2 == 1 ? N : N - 1;
            int start = nr % 2 == 1 ? 1 : 2;

            if (nr < 1 || nr > N || nc < start || nc > (col * 2) + (start - 1)) continue;
            if (map[nr][nc].dist != 0) continue;
            if (map[nr][nc].value != map[r][c].value) continue;

            //타일은 무조건 (왼쪽,오른쪽) 거리가 같아야한다.
            //따라서 왼쪽이 같은 타일일때 오른쪽 거리를 왼쪽에 넣어주고,
            //왼쪽을 큐에 넣어준다.
            bool left = false;

            if (map[nr][nc - 1].num == map[nr][nc].num) {
                left = true;
            }
            map[nr][nc].dist = map[r][c].dist + 1;
            q.push({ nr,nc });

            //왼쪽이 같은 타일
            if (left) {
                map[nr][nc - 1].dist = map[nr][nc].dist;
                q.push({ nr,nc - 1 });
            }
            //오른쪽이 같은 타일
            else {
                map[nr][nc + 1].dist = map[nr][nc].dist;
                q.push({ nr,nc + 1 });
            }
            //여태까지 지나온 타일들을 알기 위해 이전 타일을 저장해준다.
            path[map[nr][nc].num] = map[r][c].num;

            //번호가 큰 타일 찾기
            if (last < map[nr][nc].num) {
                last = map[nr][nc].num;
            }
        }
    }
}
void findPath() {
    //번호가 제일 큰 타일 찾아서 왔던 길 되돌아 가기
    int temp = last;
    way.push_back(temp);
    while (path[temp] != 0) {
        way.push_back(path[temp]);
        temp = path[temp];
    }
    cout << way.size() << endl;
    for (int i = (int)way.size() - 1; i >= 0; i--) {
        cout << way[i] << " ";
    }
    cout << endl;
}

void input_data() {
    cin >> N;
    int cnt = 1;
    for (int i = 1; i <= N; i++) {
        int col = i % 2 == 1 ? N : N - 1;
        int start = i % 2 == 1 ? 1 : 2;

        for (int j = start; j <= (col * 2) + (start - 1); j++) {
            cin >> map[i][j].value;
            map[i][j].num = (cnt + 1) / 2;
            cnt++;
        }
    }
}

void solution() {
    bfs();
    findPath();
}

int main() {
    input_data();
    solution();
    return 0;
}