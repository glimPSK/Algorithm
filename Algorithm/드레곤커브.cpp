#include <iostream>
#include <vector>
using namespace std;


int n{};
int dx[] = { 1,0,-1,0 };
int dy[] = { 0,-1,0,1 };
int nRes{};
bool v[110][110]{};


int main() {
	int y{}, x{}, d{}, g{};

	// input data
	cout << n;
	for (int i = 0; i < n; i++) {
		cin >> x >> y >> d >> g;

		// init
		vector <int> curve{};
		curve.push_back(d);

		// logic
		for (int j = 0; j < g; j++) {
			vector <int> temp = curve;
			for (int k = temp.size() - 1; k >= 0; k--) {
				curve.push_back((temp[k] + 1) % 4);
			}
		}

		v[y][x] = true;
		
		int cSize = curve.size();

		for (int j = 0; j < cSize; j++) {
			y += dy[ curve[j] ];
			x += dx[ curve[j] ];
			if (x < 0 || y < 0 || x > 100 || y > 100)	continue;
			v[y][x] = true;
		}
	}
	nRes = 0;
	for (int j = 0; j < 100; j++) {
		for (int k = 0; k < 100; k++) {
			if (v[j][k] && v[j][k + 1] && v[j + 1][k] && v[j + 1][k + 1]) {
				nRes++;
			}
		}
	}

	// result
	printf("%d\n", nRes);
	return 0;
}