#include<stdio.h>
#include<stdlib.h>
#include "diagram.h"

void iterator(diagram *d, int *pattern)
{
	diagram_print_map(d);
}


int filling_ctr;

int maxof3(int a, int b, int c)
{
	return (a > b) ? ( (c > a) ? c : a ) : ( (c > b) ? c : b );
}

int minof3(int a, int b, int c)
{
	return (a < b) ? ( (c < a) ? c : a ) : ( (c < b) ? c : b );
}

bool check_rectangle(diagram *d, int i, int j, int k)
{
	int a = d->filling[i];
	int b = d->filling[j];
	int c = d->filling[k];

	int top = maxof3(a, b, c);
	int bottom = minof3(a, b, c);
	
	return top < d->t[i] && top < d->t[k] && bottom >= d->b[i] && bottom >= d->b[k];
}

void pattern3(diagram *d, int *pattern)
{
	int *filling = d->filling;
	bool avoids = true;
	for (int i = 0; i < d->w - 2; i++) {
		for (int j = i + 1; j < d->w - 1; j++) {
			for (int k = j + 1; k < d->w; k++) {
				int a = filling[i];
				int b = filling[j];
				int c = filling[k];
				if (!check_rectangle(d, i, j, k)) {
					continue;
				}
				if (a < b) {
					if (b < c) {
						a = 1, b = 2, c = 3;
					}
					else if (a < c) {
						a = 1, b = 3, c = 2;
					}
					else {
						a = 2, b = 3, c = 1;
					}
				}
				else {
					if (a < c) {
						a = 2, b = 1, c = 3;
					}
					else if (b < c) {
						a = 3, b = 1, c = 2;
					}
					else {
						a = 3, b = 2, c = 1;
					}
				}
				if (a == pattern[0] && b == pattern[1] && c == pattern[2]) {
					avoids = false;
				}
			}
		}
	}

	if (avoids) {
		filling_ctr++;
	}
}

void iterate_over_diagrams(int *pattern1, int *pattern2, diagram *d)
{
	
}

int main(void)
{
	int testcount = 17424;
	for (int t = 0; t < testcount; t++) {
		diagram d;
		scanf("%d%d", &d.h, &d.w);
		d.b = malloc(d.w * sizeof(int));
		d.t = malloc(d.w * sizeof(int));
		d.filling = malloc(d.w * sizeof(int));

		for (int i = 0; i < d.w; i++) {
			scanf("%d", d.b + i);
		}
		for (int i = 0; i < d.w; i++) {
			scanf("%d", d.t + i);
		}
		diagram_init_map(&d);
		int pattern[] = {1, 2, 3};
		int ctr = diagram_iterate_over_fillings(&d, pattern, pattern3, false);
		printf("there are %d fillings out of %d of the given diagram avoiding 123\n", filling_ctr, ctr);
		int pattern2[] = {2, 1, 3};
		filling_ctr = 0;
		ctr = diagram_iterate_over_fillings(&d, pattern2, pattern3, false);
		printf("there are %d fillings out of %d of the given diagram avoiding 213\n", filling_ctr, ctr);
		diagram_free(&d);
	}
	return 0;
}
