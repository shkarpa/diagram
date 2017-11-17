#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

typedef struct
{
	int h, w; //height and width
	int *b; //bottom border coordinates
	int *t; //top border coordinates
	bool **map; //map of cells belonging to the diagram
} diagram;

void diagram_init_map(diagram *d)
{
	d->map = calloc(d->h, sizeof(bool *));
	for (int i = 0; i < d->h; i++) {
		d->map[i] = calloc(d->w, sizeof(bool));
	}
	for (int j = 0; j < d->w; j++) {
		for (int i = d->b[j]; i < d->t[j]; i++) {
			d->map[i][j] = true;
		}
	}
}

void diagram_print_map(diagram *d)
{
	for (int i = d->h - 1; i >= 0; i--) {
		for (int j = 0; j < d->w; j++) {
			printf("%c", (d->map[i][j]) ? '0' : '#');
		}
		printf("\n");
	}
}

void diagram_free(diagram *d)
{
	free(d->b);
	free(d->t);
	for (int i = 0; i < d->h; i++) {
		free(d->map[i]);
	}
	free(d->map);
}
