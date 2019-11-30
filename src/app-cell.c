#include "cell.h"

int main(void) {
	problem prob;
	problem* p_prob = &prob;
	prob.grid_size[0] = 10;
	prob.grid_size[1] = 10;
	
	population pop = nil();
	prob.p_pop = &pop;
	
	coordinate coord1;
	coord1.x = 9;
	coord1.y = 4;
	coordinate coord2;
	coord2.x = 0;
	coord2.y = 4;
	coordinate coord3;
	coord3.x = 9;
	coord3.y = 5;
	coordinate coord4;
	coord4.x = 0;
	coord4.y = 5;
	coordinate coord5;
	coord5.x = 3;
	coord5.y = 1;
	coordinate coord6;
	coord6.x = 2;
	coord6.y = 1;
	
	add_cell(p_prob, coord1, ALIVE);
	add_cell(p_prob, coord2, ALIVE);
	add_cell(p_prob, coord3, ALIVE);
	add_cell(p_prob, coord4, ALIVE);
	add_cell(p_prob, coord5, ALIVE);
	add_cell(p_prob, coord6, ALIVE);
	
	print_pop(p_prob);
	
	next_generation(p_prob);
	
	print_pop(p_prob);
	
	deallocate_population(p_prob);
	
	return 0;
}
