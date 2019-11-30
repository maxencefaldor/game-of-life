#include "cell.h"
#define NUMBER_RULE_1 2
#define NUMBER_RULE_2 3
#define NUMBER_RULE_3 3

int iindex(int index) {
	if (index == 0) {
		return 4;
	}
	if (index == 1) {
		return 5;
	}
	if (index == 2) {
		return 6;
	}
	if (index == 3) {
		return 7;
	}
	if (index == 4) {
		return 0;
	}
	if (index == 5) {
		return 1;
	}
	if (index == 6) {
		return 2;
	}
	if (index == 7) {
		return 3;
	}
	else {
		printf("error\n");
		return 0;
	}
}

population nil(void) {
	return NULL;
}

void add_cell(problem* p_prob, coordinate coord, status stat) {
	population* p_pop = p_prob->p_pop;

	// Allocate space for a new cell
	cell* p_cell = malloc(sizeof(cell));
	p_cell->stat = stat;
	(p_cell->coord).x = coord.x;
	(p_cell->coord).y = coord.y;

	// Update neighbors
	for (int index = 0; index <= 7; index++) {
		coordinate coord_neigh = neighbor(p_prob, p_cell, index);
		cell* p_cell_neigh = find_cell(p_prob, coord_neigh);
		(p_cell->neigh)[index] = p_cell_neigh;

		if (p_cell_neigh != NULL) {
			int new_index = iindex(index);
			(p_cell_neigh->neigh)[new_index] = p_cell;
		}
	}
	// Insert in linked list
	p_cell->next = *p_pop;
	*p_pop = p_cell;
}

void remove_cell(problem* p_prob, coordinate coord) {
	population* p_pop = p_prob->p_pop;
	cell* p_cell = *p_pop;

	if (((*p_pop)->coord).x == coord.x && ((*p_pop)->coord).y == coord.y) {
		// Update neighbors
		for (int i = 0; i <= 7; i++) {
			cell* p_cell_neigh = (*p_pop)->neigh[i];
			if (p_cell_neigh != NULL) {
				p_cell_neigh->neigh[iindex(i)] = NULL;
			}
		}
		// Remove cell
		cell* tampon = p_cell->next;
		free(p_cell);
		p_cell = NULL;
		*(p_prob->p_pop) = tampon;
	}
	else {
		cell* p_cell0 = *p_pop;
		cell* p_cell1 = NULL;
		while (p_cell0->next != NULL) {
				p_cell1 = p_cell0->next;
				if ((p_cell1->coord).x == coord.x && (p_cell1->coord).y == coord.y) {
					// Update neighbors
					for (int i = 0; i <= 7; i++) {
						cell* p_cell_neigh = p_cell1->neigh[i];
						if (p_cell_neigh != NULL) {
							p_cell_neigh->neigh[iindex(i)] = NULL;
						}
					}
					// Remove cell
					cell* tampon = p_cell1->next;
					free(p_cell1);
					p_cell1 = NULL;
					p_cell0->next = tampon;
				}
				else {
					p_cell0 = p_cell0->next;
				}
		}
	}
}

bool is_neighbor(problem* p_prob, coordinate coord1, coordinate coord2) {
	int size_x = p_prob->grid_size[0];
	int size_y = p_prob->grid_size[1];
	
	int delta_x = coord1.x - coord2.x;
	int delta_y = coord1.y - coord2.y;
	
	if (delta_x < 0) {
		delta_x = -delta_x;
	}
	if (delta_y < 0) {
		delta_y = -delta_y;
	}
	delta_x = delta_x%(size_x-1);
	delta_y = delta_y%(size_y-1);
	
	// Determine if cells are neighbors
	if ((delta_x == 0 || delta_x == 1) && (delta_y == 0 || delta_y == 1)) {
		return true;
	}
	else {
		return false;
	}
}

coordinate neighbor(problem* p_prob, cell* p_cell, int index) {
	int x = (p_cell->coord).x;
	int y = (p_cell->coord).y;
	int size_x = (p_prob->grid_size)[0];
	int size_y = (p_prob->grid_size)[1];
	coordinate coord_neigh;
	
	// Side effects
	if (index == 0) {
		coord_neigh.x = x;
		coord_neigh.y = (y+1)%size_y;
	}
	if (index == 1) {
		coord_neigh.x = (x+1)%size_x;
		coord_neigh.y = (y+1)%size_y;
	}
	if (index == 2) {
		coord_neigh.x = (x+1)%size_x;
		coord_neigh.y = y;
	}
	if (index == 3) {
		if (y == 0) {
			coord_neigh.x = (x+1)%size_x;
			coord_neigh.y = size_y-1;
		}
		else {
			coord_neigh.x = (x+1)%size_x;
			coord_neigh.y = y-1;
		}
	}
	if (index == 4) {
		if (y == 0) {
			coord_neigh.x = x;
			coord_neigh.y = size_y-1;
		}
		else {
			coord_neigh.x = x;
			coord_neigh.y = y-1;
		}
	}
	if (index == 5) {
		if (x == 0 && y == 0) {
			coord_neigh.x = size_x-1;
			coord_neigh.y = size_y-1;
		}
		else if (x == 0 && y != 0) {
			coord_neigh.x = size_x - 1;
			coord_neigh.y = y-1;
		}
		else if (x != 0 && y == 0) {
			coord_neigh.x = x-1;
			coord_neigh.y = size_y-1;
		}
		else {
			coord_neigh.x = x-1;
			coord_neigh.y = y-1;
		}
	}
	if (index == 6) {
		if (x == 0) {
			coord_neigh.x = size_x-1;
			coord_neigh.y = y;
		}
		else {
			coord_neigh.x = x-1;
			coord_neigh.y = y;
		}
	}
	if (index == 7) {
		if (x == 0) {
			coord_neigh.x = size_x-1;
			coord_neigh.y = (y+1)%size_y;
		}
		else {
			coord_neigh.x = x-1;
			coord_neigh.y = (y+1)%size_y;
		}
	}
	return coord_neigh;
}

cell* find_cell(problem* p_prob, coordinate coord) {
	population pop = *(p_prob->p_pop);
	cell* p_cell = pop;
	
	while (p_cell != NULL && ((p_cell->coord).x != coord.x || (p_cell->coord).y != coord.y)) {
		p_cell = p_cell->next;
	}
	return p_cell;
}

void next_generation(problem* p_prob) {
	// 1) Remove all DYING cells and change state of NEWBORN cells to ALIVE
	cell* p_cell = *(p_prob->p_pop);
	while (p_cell != NULL) {
		if (p_cell->stat == NEWBORN) {
			p_cell->stat = ALIVE;
			p_cell = p_cell->next;
		}
		else if (p_cell->stat == DYING) {
			cell* tampon = p_cell;
			p_cell = p_cell->next;
			remove_cell(p_prob, tampon->coord);
		}
		else {
			p_cell = p_cell->next;
		}
	}
	
	// 2) All ALIVE cells with less than two or more than three neighbors become DYING
	p_cell = *(p_prob->p_pop);
	while (p_cell != NULL) {
		int count_ALIVE = 0;
		for (int j = 0; j <= 7; j++) {
			if (p_cell->neigh[j] != NULL) {
				count_ALIVE++;
			}
		}
		if (count_ALIVE != NUMBER_RULE_1 && count_ALIVE != NUMBER_RULE_2) {
			p_cell->stat = DYING;
		}
		p_cell = p_cell->next;
	}
	
	// 3) ALL DEAD cells with exactly three neighbors become ALIVE
	p_cell = *(p_prob->p_pop);
	cell* p_cell1 = *(p_prob->p_pop);
	while (p_cell != NULL) {
		if (p_cell->stat != NEWBORN) {
			for (int j = 0; j <= 7; j++) {
				if (p_cell->neigh[j] == NULL) {
					int count_DEAD = 0;
					coordinate coord_test = neighbor(p_prob, p_cell, j);
					p_cell1 = *(p_prob->p_pop);
					while (p_cell1 != NULL) {
						if (p_cell1->stat != NEWBORN && is_neighbor(p_prob, p_cell1->coord, coord_test)) {
							count_DEAD++;
						}
						p_cell1 = p_cell1->next;
					}
					if (count_DEAD == NUMBER_RULE_3) {
						add_cell(p_prob, coord_test, NEWBORN);
					}
				}
			}
		}	
		p_cell = p_cell->next;
	}
}

void deallocate_population(problem* p_prob) {
	cell* p_cell = *(p_prob->p_pop);
	// Free memory
	while(p_cell != NULL) {
		cell* tampon = p_cell;
		p_cell = p_cell->next;
		free(tampon);
		tampon = NULL;
	}
}

void deallocate_problem(problem* p_prob) {
	deallocate_population(p_prob);
	free(p_prob->p_pop);
	p_prob->p_pop = NULL;
	free(p_prob);
	p_prob = NULL;
	
}

void print_pop(problem* p_prob) {
	if (p_prob->p_pop == NULL) {
		printf("[\n]\n");
	}
	else {
		population pop = *(p_prob->p_pop);
		int i = 1;
		cell* p_cell = pop;
		printf("[\n");
		while (p_cell != NULL) {
			printf("%d [ status = %u ; x = %d ; y = %d ; adress = %p ; 0 = %p ; 1 = %p ; 2 = %p ; 3 = %p ; 4 = %p ; 5 = %p ; 6 = %p ; 7 = %p ]\n", i, p_cell->stat, p_cell->coord.x, p_cell->coord.y, p_cell, p_cell->neigh[0], p_cell->neigh[1], p_cell->neigh[2], p_cell->neigh[3], p_cell->neigh[4], p_cell->neigh[5], p_cell->neigh[6], p_cell->neigh[7]);
			p_cell = p_cell->next;
			i++;
		}
		printf("]\n");
	}
}
