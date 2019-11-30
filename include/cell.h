/**
 * @file cell.h
 *
 * @brief Definition of the problem, the population and cells.
 *
 * @author Maxence Faldor
 * 
 * Defines different structures:
 * - a structure coordinate
 * - a structure cell
 * - a structure population which is a linked list of cells
 * - a structure problem containing all the parameters of the conway problem
 * 
 * Contains useful functions:
 * - a function to return the reciprocal index of two neighbouring cells
 * - a function to create a empty population
 * - a function to add a cell to a population
 * - a function to remove a cell from a population
 * - a function to know if two cells are neighbor considering their coordinates
 * - a function to return the coordinate of the neighbor of index i of a cell
 * - a function to get the adress of a cell in the population
 * - a function to get the population's next generation
 * - a function to deallocate a population
 * - a function to deallocate a problem
 * - a function to print a population
 */

#ifndef CELL_H
#define CELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <error.h>

/**
 * @brief An enumeration which contains the different possible status of a cell.
 */
typedef enum {
	ALIVE,
	NEWBORN,
	DYING
} status;

/**
 * @brief A structure representing the coordinate of a point in a plane.
 */
typedef struct coordinate coordinate;
struct coordinate {
	int x;
	int y;
};

/**
 * @brief A structure representing a cell.
 */
typedef struct cell cell;
struct cell {
	status stat;
	coordinate coord;
	cell* neigh[8];
	cell* next;
};

/**
 * @brief A structure representing a population. 
 */
typedef struct cell* population;

/**
 * @brief A structure representing a problem.
 */
typedef struct problem problem;
struct problem {
	int grid_size[2];
	int number_of_steps;
	population* p_pop;
};

/**
 * @brief Return the reciprocal index of two neighbouring cells.
 *
 * @param index  The index of the neighbouring cell.
 *
 * @return The reciprocal index of two neighbouring cells.
 */
int iindex(int index);

/**
 * @brief Return an empty population.
 *
 * @return An empty population.
 */
population nil(void);

/**
 * @brief Add a cell to a population.
 *
 * @param p_prob  a pointer to the problem.
 * @param coord   coordinates of the new cell.
 * @param stat    status of the new cell.
 *
 * @post A new cell is added to a population with its parameters. Neighbors of each cell are updated.
 */
void add_cell(problem* p_prob, coordinate coord, status stat);

/**
 * @brief Remove a cell from a population.
 *
 * @param p_prob  a pointer to the problem.
 * @param coord   coordinates of the cell.
 *
 * @post A cell is removed from a population. Neighbors of each cell are updated and memory is freed.
 */
void remove_cell(problem* p_prob, coordinate coord);

/**
 * @brief Enables to know if two cells are neighbor considering their coordinates.
 *
 * @param p_prob  a pointer to the problem.
 * @param coord1  coordinates of the first cell.
 * @param coord2  coordinates of the second cell.
 *
 * @return True if the cells are neighbouring. False otherwise.
 */
bool is_neighbor(problem* p_prob, coordinate coord1, coordinate coord2);

/**
 * @brief Enables to know the coordinates of the neighbor of index i of a cell considering the edges of the game.
 *
 * @param p_prob   a pointer to the problem.
 * @param my_cell  a cell representing the reference.
 * @param index    the index of the considered neighbor.
 *
 * @return True if they are neighbouring cells. False otherwise.
 */
coordinate neighbor(problem* p_prob, cell* p_cell, int index);

/**
 * @brief Find a cell in a population.
 *
 * @param p_prob  a pointer to the problem.
 * @param coord   coordinates of the first cell.
 *
 * @return A pointer to the cell of coordinates coord if it belongs to the population. NULL otherwise.
 */
cell* find_cell(problem* p_prob, coordinate coord);

/**
 * @brief Update the population to the population's next generation.
 *
 * @param p_prob  a pointer to the problem.
 *
 * @post The population is changed according to the rules of the Conway's Game of Life.
 */
void next_generation(problem* p_prob);

/**
 * @brief Free the memomy allocated to a population.
 *
 * @param p_prob  a pointer to the problem.
 *
 * @post Each cell composing the population are freed. The population is deallocated.
 */
void deallocate_population(problem* p_prob);

/**
 * @brief Free the memomy allocated to a problem.
 *
 * @param p_prob  a pointer to the problem.
 *
 * @post All the memory allocated is freed.
 */
void deallocate_problem(problem* p_prob);

/**
 * @brief print the whole population
 *
 * @param p_prob  a pointer to the problem.
 *
 * @post Each cell composing the populaton is printed in the terminal.
 */
void print_pop(problem* p_prob);

#endif
