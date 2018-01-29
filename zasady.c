#include "zasady.h"

cell_con rules(int neighbors, cell_con previous) {
	if (previous == DEAD && neighbors == 3) {
		return ALIVE;
	} else 
		if (previous == ALIVE) { 
			if (neighbors > 3 || neighbors < 2) 
				return DEAD;
			else 
				return ALIVE;
		} else 
			return DEAD;
}
cell_con rules2(int neighbors, cell_con previous){
	if (previous == DEAD && neighbors ==2){
		return ALIVE;
	} else
                if (previous == ALIVE) {
                        if (neighbors > 2 || neighbors < 1)
                                return DEAD;
                        else
                                return ALIVE;
                } else
                        return DEAD;
}

