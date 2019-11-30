/**
 * @file generate-image.h
 *
 * @brief Enable to generate an image.
 *
 * @author Maxence Faldor
 * 
 * Composed of:
 * - a function to generate an image.
 * - a function to get the number of figures in a number.
 */

#ifndef GENERATE_IMAGE_H
#define GENERATE_IMAGE_H

#include "cell.h"

/**
 * @brief Generate the image of the problem.
 *
 * @param p_prob            a pointer to the problem.
 * @param number_of_steps   number of steps of the problem.
 * @param pas               step of the problem.
 *
 * @post Generate an image in the ppm format representing the problem.
 */
void generate_image(problem* p_prob, int number_of_steps, int pas);

/**
 * @brief Gives the number of figures in the number.
 *
 * @param number  A number of int type.
 *
 * @return The number of figures in number.
 */
int number_figures(int number);

#endif
