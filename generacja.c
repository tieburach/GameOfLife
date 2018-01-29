#include <stdio.h>
#include <stdlib.h>

#include "generacja.h"

generation_t *init_gen(int rows, int cols) {
	int i, j;
	generation_t *new = (generation_t *)malloc(sizeof *new);
	if (new == NULL)
		return NULL;
	new->gen = (cell_t *)malloc((rows*cols) * sizeof *(new->gen));
	if (new->gen == NULL) {
		free(new);
		return NULL;
	}
	new->rows = rows;
	new->cols = cols;
	for (i = 0; i < rows; i++) 
		for (j = 0; j < cols; j++)
			change_condition(cell(new,i,j), DEAD);
	return new;

}

cell_t *cell(generation_t *net, int i, int j) {
	if ((i >= 0 && i < net->rows) && (j >= 0 && j < net->cols))
		return net->gen + i*net->cols + j;
	return NULL;
}

generation_t *load_from_file(FILE *in) {
	int m, n, i, j;
	generation_t *new;
	if (fscanf(in, "%d %d", &m, &n) != 2) 
		return NULL;
	new = init_gen(m, n);
	while (fscanf(in, "%d %d", &i, &j) == 2) {
		if (i > 0 && i <= m && j > 0 && j <= n)
			change_condition(cell(new, i - 1, j - 1), ALIVE);
	}
	return new;
}

void next_generation(generation_t *current, generation_t *next, int (*neighbourhood)(generation_t *, int, int)) {
	int i, j;
	for (i = 0; i < current->rows; i++) {
		for (j = 0; j < current->cols; j++) {
			change_condition(cell(next, i, j), rules(neighbourhood(current, i, j), condition(cell(current, i, j))));
		}
	}
}

void next_generation2(generation_t *current, generation_t *next, int (*neighbourhood)(generation_t *, int, int)) {
        int i, j;
        for (i = 0; i < current->rows; i++) {
                for (j = 0; j < current->cols; j++) {
                        change_condition(cell(next, i, j), rules2(neighbourhood(current, i, j), condition(cell(current, i, j))));
                }
        }
}

void free_gen(generation_t *net) {
	free(net->gen);
	free(net);
}
