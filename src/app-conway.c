#include "load.h"

int main(int argc, char** argv) {
	// 1) Load problem
	problem* p_prob = load_problem(argc, argv);
	int number_of_steps = p_prob->number_of_steps;
	
	// 2) Generate problem image and next generation
	for (int i = 1; i <= number_of_steps; i++) {
		generate_image(p_prob, number_of_steps, i);
		next_generation(p_prob);
	}
	
	// 3) Free memory
	deallocate_problem(p_prob);
	return 0;
}
