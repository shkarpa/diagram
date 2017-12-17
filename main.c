#include<stdio.h>
#include<stdlib.h>
#include "diagram.h"
#include<string.h>

void insert_sort(int *array, int len)
{
	for (int i = 1; i < len; i++) {
		int idx = i;
		while (idx > 0 && array[idx] < array[idx-1]) {
			int tmp = array[idx];
			array[idx] = array[idx-1];
			array[idx-1] = tmp;
			idx--;
		}
	}
}

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

bool avoids_pattern3(diagram *d, diagram *to_avoid)
{
	int *pattern = to_avoid->filling;
	int *filling = d->filling;
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
				if (a == pattern[0] + 1 && b == pattern[1] + 1 && c == pattern[2] + 1) {
					return false;
				}
			}
		}
	}
	return true;
}

void pattern3(diagram *d, diagram *to_avoid)
{
	if (avoids_pattern3(d, to_avoid)) {
		//diagram_print_map(d);
		//printf("\n");
		filling_ctr++;
	}
}

bool avoids_diag4(diagram *d, diagram *to_avoid)
{
	int n = d->h;
	for (int col1 = 0; col1 < n-3; col1++) {
		for (int col2 = col1 + 1; col2 < n-2; col2++) {
			for (int col3 = col2 + 1; col3 < n-1; col3++) {
				for (int col4 = col3 + 1; col4 < n; col4++) {
					int cols[] = {col1, col2, col3, col4};
					int rows[] = {d->filling[col1], d->filling[col2], d->filling[col3], d->filling[col4]};
					insert_sort(rows, 4);
					bool matches = true;
					for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 4; j++) {
							if (to_avoid->map[i][j] != d->map[rows[i]][cols[j]]) {
								matches = false;
							}
						}
					}
					if (matches) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

void hypo(diagram *d, diagram *to_avoid)
{
	if (avoids_pattern3(d, &to_avoid[0])) {
		 if (avoids_diag4(d, &to_avoid[1])) {
			filling_ctr++;
		 }
	//	 else {
	//		diagram_print_map(d);
	//	 	printf("smejd\n\n");
	//	 }
	}
}

void hypo_init(diagram *d)
{
	for (int i = 0; i < 4; i++) {
		d->b[i] = 0;
		d->t[i] = 4;
	}
	d->b[3] = 1;
	d->t[0] = 3;
	diagram_init_map(d);

	int *filling = d->filling;
	filling[0] = 0;
	filling[1] = 1;
	filling[2] = 3;
	filling[3] = 2;
	for (int i = 0; i < 4; i++) {
		d->map[filling[i]][i] = '1';
	}
}

int main(void)
{
	int testcount = 1764;

	for (int t = 0; t < testcount; t++) {
		
		diagram d;
		int h, w;
		scanf("%d%d", &h, &w);
		diagram_init(&d, h, w);

		for (int i = 0; i < d.w; i++) {
			scanf("%d", d.b + i);
		}
		for (int i = 0; i < d.w; i++) {
			scanf("%d", d.t + i);
		}

		diagram_init_map(&d);
			
		diagram to_avoid[2];
		diagram_init(to_avoid, 3, 3);
		to_avoid[0].filling[0] = 0;	
		to_avoid[0].filling[1] = 1;	
		to_avoid[0].filling[2] = 2;	
		diagram_init(&to_avoid[1], 4, 4);
		hypo_init(&to_avoid[1]);

		filling_ctr = 0;
		int ctr1 = diagram_iterate_over_fillings(&d, to_avoid, hypo, false);
		int a = filling_ctr;
			
		to_avoid[0].filling[0] = 2;
		to_avoid[0].filling[1] = 1;
		to_avoid[0].filling[2] = 0;
		filling_ctr = 0;
		int ctr2 = diagram_iterate_over_fillings(&d, to_avoid, pattern3, false);
		int b = filling_ctr;

		to_avoid[0].filling[0] = 0;	
		to_avoid[0].filling[1] = 1;	
		to_avoid[0].filling[2] = 2;	
		filling_ctr = 0;
		int ctr3 = diagram_iterate_over_fillings(&d, to_avoid, pattern3, false);
		int c = filling_ctr;

		if (a < b) {
		//if (a != b && c != a) {
			diagram_print_map(&d);
			printf("there are %d fillings out of %d of the given diagram avoiding 123\n", c, ctr3);
			printf("there are %d fillings out of %d of the given diagram avoiding 123 and hypo\n", a, ctr1);
			printf("there are %d fillings out of %d of the given diagram avoiding 321\n", b, ctr2);
		}
		diagram_free(&d);
	}
	return 0;
}
