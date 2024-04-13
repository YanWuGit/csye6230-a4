#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

#define GRID_SIZE 9

// Function prototypes
bool read_puzzle_from_file(const char* filename, int puzzle[GRID_SIZE][GRID_SIZE]);
void print_puzzle(int puzzle[GRID_SIZE][GRID_SIZE]);

#endif // UTILS_H
