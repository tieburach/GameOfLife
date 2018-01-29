#ifndef KOMORKA_H
#define KOMORKA_H

typedef enum{DEAD, ALIVE} cell_con;

typedef struct{
	cell_con condition;
} cell_t;

void change_condition(cell_t *cell, cell_con new_condition);

cell_t *init_cell();

cell_con condition(cell_t *cell);

#endif
