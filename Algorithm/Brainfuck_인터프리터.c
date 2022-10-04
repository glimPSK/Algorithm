// https://computer-choco.tistory.com/447
#include <stdio.h>

int msize;
int csize;
int isize;
int pointer;
int input_index;

unsigned char codes[4096];
unsigned char inputs[4096];
unsigned char memory[100010];
int jumps[4096];

int stack[5000];
int stack_pos[5000];
int cptr;
int sp;
int tc;

void preprocess(void)
{
	sp = 0;
	for (int i = 0; i < csize; i++) {
		if (codes[i] == '[') {
			sp++;
			stack[sp] = i;
		}
		if (codes[i] == ']') {
			jumps[stack[sp]] = i;
			jumps[i] = stack[sp];
			sp--;
		}
	}
}

int do_code(int index)
{
	int ret = index + 1;

	if (codes[index] == '-') {
		memory[pointer] = (memory[pointer] + 256 - 1) % 256;
	}
	else if (codes[index] == '+') {
		memory[pointer] = (memory[pointer] + 1) % 256;
	}
	else if (codes[index] == '<') {
		pointer = (pointer + msize - 1) % msize;
	}
	else if (codes[index] == '>') {
		pointer = (pointer + 1) % msize;
	}
	else if (codes[index] == '[') {
		if (memory[pointer] == 0) { /* loop pass */
			ret = jumps[index] + 1;
		}
		else {
			stack_pos[sp] = cptr;
			stack[sp] = index;
			sp++;
		}
	}
	else if (codes[index] == ']') {
		if (memory[pointer] != 0) {
			ret = jumps[index] + 1;
			stack_pos[sp - 1] = cptr; /* update */
		}
		else sp--; /* loop end */
	}
	else if (codes[index] == ',') {
		if (input_index >= isize) {
			memory[pointer] = 255;
		}
		else {
			memory[pointer] = inputs[input_index++];
		}
	} // pass "."

	return ret;
}

void run(void)
{
	int max_code = 50000001;
	int index = 0;
	int i;

	pointer = 0;
	input_index = 0;
	sp = 0;
	cptr = 0;

	/* terminates within 50 000 000 instructions */
	while (max_code--) {
		if (index >= csize) {
			printf("Terminates\n");
			return;
		}
		index = do_code(index);
		cptr++;
	}

	/* at most 50 000 000 instructions within infinite loop */
	max_code = 50000001;
	while (max_code--) {
		index = do_code(index);
		cptr++;
	}

	for (i = 0; i < sp; i++) {
		if (cptr - 1 - stack_pos[i] <= 50000000) {
			printf("Loops %d %d\n", stack[i], jumps[stack[i]]);
			break;
		}
	}
}

void init(void)
{
	scanf("%d %d %d", &msize, &csize, &isize);

	for (int i = 0; i < msize; i++) {
		memory[i] = 0;
	}
	for (int i = 0; i < csize; i++) {
		scanf(" %c", &codes[i]);
	}
	getchar();
	for (int i = 0; i < isize; i++) {
		scanf(" %c", &inputs[i]);
	}
	getchar();
}

int main()
{
	scanf("%d", &tc);
	for (int t = 1; t <= tc; t++) {

		/* get input & init arrays */
		init();

		/* [[ ]] find sets */
		preprocess();

		/* start codes */
		run();
	}
}