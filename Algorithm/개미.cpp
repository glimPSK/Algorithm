#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int N1 = 0;
int N2 = 0;
int T;

int main() {
	cin >> N1 >> N2;

	string right, left;
	cin >> right;
	cin >> left;
	cin >> T;
	reverse(right.begin(), right.end());
	string ant = right + left;
	int time = 0;
	while (time < T) {
		for (int i = 0; i < N1 + N2 - 1; i++) {
			if (right.find(ant[i]) != string::npos && left.find(ant[i + 1]) != string::npos) {
				swap(ant[i], ant[i + 1]);
				i++;
			}
		}
		time += 1;
	}
	cout << ant;

	return 0;
}