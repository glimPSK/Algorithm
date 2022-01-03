#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

int n{};
int arr[10000010]{};
int b{}, c{};

int main() {
	//input
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	scanf("%d %d", &b, &c);

	//init
	long long int nRes = 0;

	//logic
	for (int i = 0; i < n; i++) {
		long long int cnt = 0;
		if (arr[i] > 0) {
			arr[i] -= b;
			cnt++;
			if (arr[i] > 0) {
				if (arr[i] % c > 0) {
					cnt += (arr[i] / c) + 1;
				}
				else {
					cnt += (arr[i] / c);
				}
			}
		}
		nRes += cnt;
	}

	//result
	printf("%lld\n", nRes);
	return 0;
}