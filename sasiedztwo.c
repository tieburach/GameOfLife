#include "sasiedztwo.h"

int Moore_ngbh(generation_t *net, int i, int j) {
        int a, b, result = 0;
        for (a = i - 1; a <= i + 1; a++) {
                if (a < 0 || a >= net->rows)
                        continue;
                for (b = j - 1; b <= j + 1; b++) {
                        if ((a == i && b == j) || b < 0 || b >= net->cols)
                                continue;
                        if (condition(cell(net,a,b)) == ALIVE){
                                result++;
		
                			}
			}
        }
        return result;
	
}
int Neumann_ngbh(generation_t *net, int i, int j) {
	int result = 0;
	if (i < net->rows-1){
		if (condition(cell(net,i+1,j)) == ALIVE)
                        result++;
		}
	if (i > 0){
		if (condition(cell(net,i-1,j)) == ALIVE)
                        result++;
		}
	if (j<net->cols-1){
 		if (condition(cell(net,i,j+1)) == ALIVE)
                        result++;
		}	
	if(j > 0){
		if (condition(cell(net,i,j-1)) == ALIVE)
                	result++;

		}
	return result;
}

