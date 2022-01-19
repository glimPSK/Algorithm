#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

/* cube */
char white_U[3][3];
char orange_B[3][3];
char green_L[3][3];
char blue_R[3][3];
char red_F[3][3];
char yellow_D[3][3];
/* //cube */

int T, n;
char cmd_Demesion, cmd_dir;

void initCube() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			white_U[i][j] = 'w';
			orange_B[i][j] = 'o';
			green_L[i][j] = 'g';
			blue_R[i][j] = 'b';
			red_F[i][j] = 'r';
			yellow_D[i][j] = 'y';
		}
	}
}
void simulation(char cmd_Demesion, char cmd_dir) {
	switch (cmd_Demesion)
	{
	case 'L':
		if (cmd_dir == '-') {
			char temp[3][3];
			for (int i = 0; i < 3; i++) {
				temp[i][0] = white_U[i][0];
				white_U[i][0] = red_F[i][0];//
				red_F[i][0] = yellow_D[2 - i][2];
				yellow_D[2 - i][2] = orange_B[2 - i][2];
				orange_B[2 - i][2] = temp[i][0];
			}
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					temp[2 - j][i] = green_L[i][j];
				}
			}
			memcpy(green_L, temp, sizeof(green_L));
		}
		else {
			char temp[3][3];
			for (int i = 0; i < 3; i++) {
				temp[i][0] = white_U[i][0];
				white_U[i][0] = orange_B[2 - i][2];
				orange_B[2 - i][2] = yellow_D[2 - i][2];
				yellow_D[2 - i][2] = red_F[i][0];
				red_F[i][0] = temp[i][0];
			}
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					temp[j][2 - i] = green_L[i][j];
				}
			}
			memcpy(green_L, temp, sizeof(green_L));
		}
		break;

	case 'R':
		if (cmd_dir == '-') {
			char temp[3][3];
			for (int i = 0; i < 3; i++) {
				temp[i][0] = white_U[i][2];
				white_U[i][2] = orange_B[2 - i][0];
				orange_B[2 - i][0] = yellow_D[2 - i][0];
				yellow_D[2 - i][0] = red_F[i][2];
				red_F[i][2] = temp[i][0];
			}
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					temp[2 - j][i] = blue_R[i][j];
				}
			}
			memcpy(blue_R, temp, sizeof(blue_R));
		}
		else {
			char temp[3][3];
			for (int i = 0; i < 3; i++) {
				temp[i][0] = white_U[i][2];
				white_U[i][2] = red_F[i][2];//
				red_F[i][2] = yellow_D[2 - i][0];
				yellow_D[2 - i][0] = orange_B[2 - i][0];
				orange_B[2 - i][0] = temp[i][0];
			}
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					temp[j][2 - i] = blue_R[i][j];
				}
			}
			memcpy(blue_R, temp, sizeof(blue_R));
		}
		break;

	case 'F':
		if (cmd_dir == '-') {
			char temp[3][3];
			for (int i = 0; i < 3; i++) {
				temp[i][0] = white_U[2][i];
				white_U[2][i] = blue_R[i][0];
				blue_R[i][0] = yellow_D[2][i];
				yellow_D[2][i] = green_L[2 - i][2];
				green_L[2 - i][2] = temp[i][0];
			}
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					temp[2 - j][i] = red_F[i][j];
				}
			}
			memcpy(red_F, temp, sizeof(red_F));
		}
		else {
			char temp[3][3];
			for (int i = 0; i < 3; i++) {
				temp[i][0] = white_U[2][i];
				white_U[2][i] = green_L[2 - i][2];
				green_L[2 - i][2] = yellow_D[2][i];
				yellow_D[2][i] = blue_R[i][0];
				blue_R[i][0] = temp[i][0];
			}
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					temp[j][2 - i] = red_F[i][j];
				}
			}
			memcpy(red_F, temp, sizeof(red_F));
		}
		break;

	case 'B':
		if (cmd_dir == '-') {
			char temp[3][3];
			for (int i = 0; i < 3; i++) {
				temp[i][0] = white_U[0][i];
				white_U[0][i] = green_L[2 - i][0];
				green_L[2 - i][0] = yellow_D[0][i];
				yellow_D[0][i] = blue_R[i][2];
				blue_R[i][2] = temp[i][0];
			}
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					temp[2 - j][i] = orange_B[i][j];
				}
			}
			memcpy(orange_B, temp, sizeof(orange_B));
		}
		else {
			char temp[3][3];
			for (int i = 0; i < 3; i++) {
				temp[i][0] = white_U[0][i];
				white_U[0][i] = blue_R[i][2];
				blue_R[i][2] = yellow_D[0][i];
				yellow_D[0][i] = green_L[2 - i][0];
				green_L[2 - i][0] = temp[i][0];
			}

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					temp[j][2 - i] = orange_B[i][j];
				}
			}
			memcpy(orange_B, temp, sizeof(orange_B));
		}
		break;

	case 'U':
		if (cmd_dir == '-') {
			char temp[3][3];
			for (int i = 0; i < 3; i++) {
				temp[i][0] = red_F[0][i];
				red_F[0][i] = green_L[0][i];
				green_L[0][i] = orange_B[0][i];
				orange_B[0][i] = blue_R[0][i];
				blue_R[0][i] = temp[i][0];
			}
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					temp[2 - j][i] = white_U[i][j];
				}
			}
			memcpy(white_U, temp, sizeof(white_U));
		}
		else {
			char temp[3][3];
			for (int i = 0; i < 3; i++) {
				temp[i][0] = red_F[0][i];
				red_F[0][i] = blue_R[0][i];
				blue_R[0][i] = orange_B[0][i];
				orange_B[0][i] = green_L[0][i];
				green_L[0][i] = temp[i][0];
			}

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					temp[j][2 - i] = white_U[i][j];
				}
			}
			memcpy(white_U, temp, sizeof(white_U));
		}
		break;

	case 'D':
		if (cmd_dir == '-') {
			char temp[3][3];
			for (int i = 0; i < 3; i++) {
				temp[i][0] = red_F[2][i];
				red_F[2][i] = blue_R[2][i];
				blue_R[2][i] = orange_B[2][i];
				orange_B[2][i] = green_L[2][i];
				green_L[2][i] = temp[i][0];
			}
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					temp[2 - j][i] = yellow_D[i][j];
				}
			}
			memcpy(yellow_D, temp, sizeof(yellow_D));
		}
		else {
			char temp[3][3];
			for (int i = 0; i < 3; i++) {
				temp[i][0] = red_F[2][i];
				red_F[2][i] = green_L[2][i];
				green_L[2][i] = orange_B[2][i];
				orange_B[2][i] = blue_R[2][i];
				blue_R[2][i] = temp[i][0];
			}

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					temp[j][2 - i] = yellow_D[i][j];
				}
			}
			memcpy(yellow_D, temp, sizeof(yellow_D));
		}
		break;
	}
	return;
}

int main() {
	//Input Data
	scanf("%d ", &T);
	for (int i = 0; i < T; i++) {
		scanf("%d ", &n);
		//Init
		initCube();
		//Logic
		for (int j = 0; j < n; j++) {
			scanf(" %c%c", &cmd_Demesion, &cmd_dir);
			simulation(cmd_Demesion, cmd_dir);
		}
		//Result
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				printf("%c", white_U[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}