#include<iostream>
#define max(a,b) a > b ? a : b
using namespace std;

int M, N, ans;
int land[1002][1002];
int dp[1002][1002];

int minfunc(int a, int b, int c)
{
	if (a < b)
	{
		if (a < c) return a;
		else return c;
	}
	else
	{
		if (b < c) return b;
		else return c;
	}
}
int main(void)
{
	cin >> M >> N;

	for (int i = 1; i <= M; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> land[i][j];

			if (i == 1 || j == 1)
			{
				if (land[i][j]) dp[i][j] = 0;
				else dp[i][j] = 1;
			}
		}
	}

	for (int i = 2; i <= M; i++)
	{
		for (int j = 2; j <= N; j++)
		{
			// 목장일 지을 수 있는 땅일 때
			if (land[i][j] == 0)
			{
				// 정사각형을 선 목장과 합쳐서 만들 수 있으면 합쳐서 만든다
				if (land[i - 1][j - 1] == 0 && land[i - 1][j] == 0 && land[i][j - 1] == 0)
				{
					dp[i][j] = minfunc(dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]) + 1;
				}
				// 정사각형을 선 목장과 합쳐서 만들 수 없으면 1을 넣는다.
				else
				{
					dp[i][j] = 1;
				}
			}
			// 목장을 지을 수 없는 땅일 때
			else
			{
				dp[i][j] = 0;
			}
		}
	}

	for (int i = 1; i <= M; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			ans = max(ans, dp[i][j]);
		}
	}

	cout << ans;

	return 0;
}