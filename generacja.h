#ifndef GENERACJA_H
#define GENERACJA_H

#include <stdio.h>

#include "komorka.h"
#include "zasady.h"

typedef struct {
	cell_t *gen;
	int rows;
	int cols;
} generation_t;

generation_t *init_gen(int rows, int cols);

generation_t *load_from_file(FILE *in);

void next_generation(generation_t *current, generation_t *next, int (*neighbourhood)(generation_t *, int, int));

void next_generation2(generation_t *current, generation_t *next, int (*neighbourhood)(generation_t *, int, int));

cell_t *cell(generation_t *net, int i, int j);

void free_gen(generation_t *net);

#endif
