#include <stdlib.h>

#include "komorka.h"

void change_condition(cell_t *cell, cell_con new_condition){
	cell->condition = new_condition;
}

cell_t *init_cell(){
	cell_t *new = malloc(sizeof *new);
	change_condition(new, DEAD);
	return new;
}

cell_con condition(cell_t *cell) {
	return cell->condition;
}
