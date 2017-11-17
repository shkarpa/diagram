#include<stdio.h>
#include<stdlib.h>
#include "diagram.h"

int main(void)
{
	diagram d;
	scanf("%d%d", &d.h, &d.w);
	d.b = malloc(d.w * sizeof(int));
	d.t = malloc(d.w * sizeof(int));
	for (int i = 0; i < d.w; i++) {
		scanf("%d", d.b + i);
	}
	for (int i = 0; i < d.w; i++) {
		scanf("%d", d.t + i);
	}
	diagram_init_map(&d);
	diagram_print_map(&d);
	diagram_free(&d);
	return 0;
}
