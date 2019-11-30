#include "generate-image.h"

void generate_image(problem* p_prob, int number_of_steps, int pas) {
	int number_of_zeros = number_figures(number_of_steps);
	char name[14+number_of_zeros];
	name[0] = 'o';
	name[1] = 'u';
	name[2] = 't';
	name[3] = '/';
	name[4] = 'f';
	name[5] = 'r';
	name[6] = 'a';
	name[7] = 'm';
	name[8] = 'e';
	
	for (int i = 9; i < 9 + number_of_zeros; i++) {
		name[i] = '0';
	}

	int size_pas = number_figures(pas);
	char s_pas[size_pas];
	sprintf(s_pas, "%d", pas);
	for (int i = 0; i <= size_pas-1; i++) {
		name[8+number_of_zeros-i] = s_pas[size_pas-1-i];
	}

	name[8+number_of_zeros+1] = '.';
	name[8+number_of_zeros+2] = 'p';
	name[8+number_of_zeros+3] = 'p';
	name[8+number_of_zeros+4] = 'm';
	name[8+number_of_zeros+5] = '\0';
	
	FILE *p_file = NULL;
	p_file = fopen(name, "w");
	if (p_file == NULL) {
        error(1, 0, "Cannot write\n");
    }
    
    	// Geneate file according to defined syntax
	fprintf(p_file, "P3\n");
	fprintf(p_file, "%d %d\n", p_prob->grid_size[0], p_prob->grid_size[1]);
	fprintf(p_file, "255\n");
	for (int j = 0; j <= p_prob->grid_size[1]-1; j++) {
		for (int i = 0; i <= p_prob->grid_size[0]-1; i++) {
			coordinate coord;
			coord.x = i;
			coord.y = j;
			cell* p_cell = find_cell(p_prob, coord);
			if (p_cell == NULL) {
				fprintf(p_file, "  0   0   0  ");
			}
			else {
				if (p_cell->stat == ALIVE) {
					fprintf(p_file, "255 255 255  ");
				}
				if (p_cell->stat == NEWBORN) {
					fprintf(p_file, "255   0   0  ");
				}
				if (p_cell->stat == DYING) {
					fprintf(p_file, "  0   0 255  ");
				}
			fprintf(p_file, "\n");
			}
		}
	}
    fclose(p_file);
    p_file = NULL;
}

int number_figures(int number) {
	int compteur = 0;
	double number2 = number;
	do {
		number2 = number2/10;
		compteur++;
	} while (number2 >= 1);
	return compteur;
}
