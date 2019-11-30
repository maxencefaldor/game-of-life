#include "generate-image.h"

int main(void) {
	problem prob;
	population pop = nil();
	prob.p_pop = &pop;
	prob.grid_size[0] = 10;
	prob.grid_size[1] = 10;
	prob.number_of_steps = 100;
	
	problem* p_prob = &prob;
	
	coordinate coord1;
	coord1.x = 0;
	coord1.y = 0;
	
	coordinate coord2;
	coord2.x = 9;
	coord2.y = 9;
	
	coordinate coord3;
	coord3.x = 0;
	coord3.y = 9;
	
	coordinate coord4;
	coord4.x = 9;
	coord4.y = 0;
	
	add_cell(p_prob, coord1, ALIVE);
	add_cell(p_prob, coord2, NEWBORN);
	add_cell(p_prob, coord3, ALIVE);
	add_cell(p_prob, coord4, DYING);


	for (int i = 1; i <= 30; i++) {
		generate_image(p_prob, p_prob->number_of_steps, i);
	}
	
	deallocate_population(p_prob);
}
