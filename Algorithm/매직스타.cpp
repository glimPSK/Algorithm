/*
# 3967 매직 스타

Q)   수를 다 채워서 매직 스타 만들기

S)   1. 총 6개의 라인의 합이 동일해야 함
   2. 2개씩 겹치는 숫자들이 총 6개
   3. 수는 총 12개 A~L까지

A)   1. 맵에 있는 정보 담기

*/
#include <iostream>
using namespace std;
#define SIZE 10

int map[SIZE][SIZE]{};

void input_data() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            char cData;
            cin >> cData;
            //init
            if (cData == '.') {
                map[i][j] = -1;
            }
            else if (cData == 'x') {
                map[i][j] = 0;
            }
            else {
                map[i][j] = cData - 64;
            }
        }
    }
}

void solution() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            cout << map[i][j] << "\t";
        }
        cout << endl;
    }
}

int main() {

    input_data();
    
    solution();
    
    return 0;
}