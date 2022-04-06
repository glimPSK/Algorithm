#include <iostream>
using namespace std;
#define SIZE 1001

int N{};
int dp[SIZE]{};

void input_data() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        int num{};
        cin >> num;
        if (dp[i] == 0)
            continue;
        for (int j = 1; (j <= num) && (i + j <= 1000); j++) {
            if (dp[i + j] > dp[i] + 1 || dp[i + j] == 0)
                dp[i + j] = dp[i] + 1;
        }
    }
}

void solution() {
    if (dp[N] == 0)
        cout << "-1" << endl;
    else
        cout << dp[N] - 1 << endl;
}

void init() {
    dp[1] = 1;
}

int main() {
    init();
    input_data();
    solution();
    return 0;
}
