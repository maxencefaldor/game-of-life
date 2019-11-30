#include "load.h"

problem* load_problem(int argc, char** argv) {
	// 1) Open problem's definition file
	FILE *p_file = NULL;
	p_file = fopen(argv[1], "r");
	if (p_file == NULL) {
        error(1, 0, "Cannot read file %s!\n", argv[1]);
    }
	// 2) Get problem parameters from file
	int size_x;
	int size_y;
	int number_of_steps;
	fscanf(p_file, "%d %d\n", &size_x, &size_y);
	fscanf(p_file, "%d\n", &number_of_steps);
	
	// 3) Update problem
	problem* p_prob = malloc(sizeof(problem));
	population*  p_pop = malloc(sizeof(population));

	*p_pop = nil();
	p_prob->p_pop = p_pop;
	p_prob->grid_size[0] = size_x;
	p_prob->grid_size[1] = size_y;
	p_prob->number_of_steps = number_of_steps;
	
	char caractere;
	coordinate coord;
	for (int j = 0; j < size_y; j++) {
		for(int i = 0; i < size_x; i++) {
			caractere = fgetc(p_file);
			while (caractere != 'o' && caractere != '.') {
				caractere = fgetc(p_file);
			}
			if (caractere == 'o') {
				coord.x = i;
				coord.y = j;
				add_cell(p_prob, coord, ALIVE);
			}
		}
	}
	// 4) Close file
	fclose(p_file);
	p_file = NULL;
	
	return p_prob;
}
