/*
Q)
*/

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

#define SIZE 21
#define MAX 987987987

typedef struct customer {
    int bx, by, ax, ay;
};

customer info[400];
int N{}, M{};
int fuel{};
int MAP[SIZE][SIZE]{};
int dist[SIZE][SIZE]{};
int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };
int taxi_x{}, taxi_y{};
int total{};
bool visit[410];

queue <pair<int, int>> Q{};

// 승객의 좌표를 x,y좌표 순으로 정렬
bool cmp(customer A, customer B) {
    if (A.bx <= B.bx) {
        if (A.bx == B.bx) {
            if (A.by < B.by) {
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}

//현재 위치에서 가장 가까운 승객을 찾음
int find_customer() {
    Q.push(make_pair(taxi_x, taxi_y));

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            dist[i][j] = MAX;

    dist[taxi_x][taxi_y] = 0;
    int idx = 404;
    int far = MAX;
    int nx = 30;
    int ny = 30;

    //현재 택시에서 모든 좌표까지 거리 구하기
    while (!Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx<1 || ny<1 || nx>N || ny>N || MAP[nx][ny] == 1) continue;
            if (dist[nx][ny] > dist[x][y] + 1) {
                dist[nx][ny] = dist[x][y] + 1;
                Q.push(make_pair(nx, ny));
            }
        }
    }

    // 현재 택시 위치에서 가장 가까운 승객 찾기, 단 이미 방문한 승객은 Pass
    for (int i = 0; i < M; i++) {
        if (visit[i]) continue;

        if (dist[info[i].bx][info[i].by] == far) {
            if (info[i].bx < nx) {
                nx = info[i].bx;
                ny = info[i].by;
                idx = i;
            }
            else if (info[i].bx == nx && info[i].by < ny) {
                nx = info[i].bx;
                ny = info[i].by;
                idx = i;
            }
            else continue;
        }
        else if (dist[info[i].bx][info[i].by] < far) {
            far = dist[info[i].bx][info[i].by];
            nx = info[i].bx;
            ny = info[i].by;
            idx = i;
        }
    }
    // 승객을  찾았다면 그 노드는 방문 표시, 택시 이동
    visit[idx] = true;
    taxi_x = nx, taxi_y = ny;
    fuel -= dist[taxi_x][taxi_y];

    return idx;
}

//택시가 승객의 목적지로 이동하는 함수
void move_dest()
{
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            dist[i][j] = 99999999;

    Q.push(make_pair(taxi_x, taxi_y));
    dist[taxi_x][taxi_y] = 0;

    while (!Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx<1 || ny<1 || nx>N || ny>N || MAP[nx][ny] == 1) continue;
            if (dist[nx][ny] > dist[x][y] + 1) {
                dist[nx][ny] = dist[x][y] + 1;
                Q.push(make_pair(nx, ny));
            }
        }
    }
}

int solution() {
    //init
    total = M;
    sort(info, info + M, cmp);

    while (true) {
        if (fuel < 0) return -1;
        if (total == 0) return fuel;
        int idx = find_customer();
        if (idx == 404) return -1;
        move_dest();
        if (fuel < dist[info[idx].ax][info[idx].ay]) return -1; //만약 연료 부족하면 -1리턴 그렇지 않다면 연료 충전
        fuel += dist[info[idx].ax][info[idx].ay];
        taxi_x = info[idx].ax, taxi_y = info[idx].ay;
        total--;
    }
    return -1;
}

void input_data() {
    cin >> N >> M >> fuel;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> MAP[i][j];

    cin >> taxi_x >> taxi_y;

    for (int i = 0; i < M; i++)
        cin >> info[i].bx >> info[i].by >> info[i].ax >> info[i].ay;

}
int main() {
    //input
    input_data();

    //solution
    cout << solution();

    return 0;

}
