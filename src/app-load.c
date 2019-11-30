#include "load.h"

int main(int argc, char** argv) {
	problem* p_prob = load_problem(argc, argv);
	print_pop(p_prob);
	deallocate_problem(p_prob);
	return 0;
}
