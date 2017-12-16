#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

typedef struct
{
	int h, w; //height and width
	int *b; //bottom border coordinates
	int *t; //top border coordinates
	char **map; //map of cells belonging to the diagram
	int *filling; // filling[i] = j means that there is a 1 at [j,i]
} diagram;


void diagram_init_map(diagram *d)
{
	d->map = calloc(d->h, sizeof(char *));
	for (int i = 0; i < d->h; i++) {
		d->map[i] = calloc(d->w, sizeof(char));
	}
	for (int i = 0; i < d->h; i++) {
		for (int j = 0; j < d->w; j++) {
			d->map[i][j] = '#';
		}
	}
	for (int j = 0; j < d->w; j++) {
		for (int i = d->b[j]; i < d->t[j]; i++) {
			d->map[i][j] = '0';
		}
	}
}

void diagram_print_map(diagram *d)
{
	for (int i = d->h - 1; i >= 0; i--) {
		for (int j = 0; j < d->w; j++) {
			printf("%c", d->map[i][j]);
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
	free(d->filling);
}

static bool used[100];
static int ctr;

static void iterate(diagram *d, int *pattern, void function(diagram *, int *), int column, bool partial)
{
	if (column >= d->w) {
		ctr++;
		function(d, pattern);
		return;
	}

	for (int i = d->b[column]; i < d->t[column]; i++) {
		if (!used[i]) {
			used[i] = true;
			d->filling[column] = i;
			d->map[i][column] = '1';
			iterate(d, pattern, function, column + 1, partial);
			d->map[i][column] = '0';
			used[i] = false;
		}	
	}

	if (partial) {
		iterate(d, pattern, function, column + 1, partial);
	}
}

int diagram_iterate_over_fillings(diagram *d, int *pattern, void function(diagram *, int *), bool partial)
{
	ctr = 0;
	iterate(d, pattern, function, 0, partial);		
	return ctr;
}
