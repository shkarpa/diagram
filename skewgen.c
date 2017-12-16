/* generate all reasonable skew diagrams NxN */

#include<stdio.h>

#define MAXN 10

int N;
int CTR;

int b[MAXN]; //bottom border
int t[MAXN]; //top border

void print()
{
	CTR++;
	printf("%d %d\n", N, N);
	for (int i = 0; i < N; i++) {
		printf("%d%s", b[i], (i < N-1) ? " " : "\n");
	}
	for (int i = 0; i < N; i++) {
		printf("%d%s", t[i], (i < N-1) ? " " : "\n");
	}
}

void generate_top(int col)
{
	if (col == N-1) {
		t[col] = N;
		print();
		return;
	}
	
	int max = (t[col-1] > col + 1) ? t[col-1] : col + 1;
	for (int i = max; i <= N; i++) {
		t[col] = i;
		generate_top(col + 1);
	}
}

// col >= 1, always b[0] = 0
void generate_bottom(int col)
{
	if (col == N) {
		for (int i = b[0] + 1; i <= N; i++) {
			t[0] = i;
			generate_top(1);
		}
		return;
	}

	for (int i = b[col-1]; i <= col; i++) {
		b[col] = i;
		generate_bottom(col + 1);
	}
}

int main(int argc, char** argv)
{
	scanf("%d", &N);
	generate_bottom(0);
	printf("%d\n", CTR);
	return 0;
}
