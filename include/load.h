/**
 * @file load.h
 *
 * @brief Enable to load an image.
 *
 * @author Maxence Faldor
 * 
 * Composed of:
 * - a function to load a data file .txt representing the initial state of a problem.
 */

#ifndef LOAD_H
#define LOAD_H

#include "generate-image.h"

/**
 * @brief Load a problem from a .txt file.
 * 
 * @param argc  An int given in the terminal
 * @param argv  A char** given in the terminal
 *
 * @return A pointer to a problem with a population and parameters loaded from a .txt file.
 */
problem* load_problem(int argc, char** argv);

#endif
