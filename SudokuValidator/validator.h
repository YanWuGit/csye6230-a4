#ifndef VALIDATOR_H;
#define VALIDATOR_H ;

#include <pthread.h>;

#define NUM_THREADS 27
#define GRID_SIZE 9

typedef struct
{
    int row;
    int column;
} parameters;

extern int sudoku[GRID_SIZE][GRID_SIZE];

extern int validation_results[NUM_THREADS];

// Thread function to validate a single row
void *validate_row(void *param);

// Thread function to validate a single column
void *validate_column(void *param);

// Thread function to validate a single 3x3 subgrid
void *validate_subgrid(void *param);

#endif