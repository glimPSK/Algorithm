#include <iostream>
#include <algorithm>
using namespace std;
#define SIZE 1010

int N{}, M{};
int map[SIZE][SIZE]{};
int dp[SIZE][SIZE]{};

void input_data() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> map[i][j];
        }
    }
}

void solution() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            int nRes = 0;
            nRes = max(dp[i - 1][j - 1], max(dp[i - 1][j], dp[i][j - 1]));
            dp[i][j] = nRes + map[i][j];
        }
    }
    cout << dp[N][M] << endl;
}

int main() {
    input_data();
    solution();
    return 0;
}
