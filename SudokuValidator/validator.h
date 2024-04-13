#ifndef VALIDATOR_H
#define VALIDATOR_H

#define NUM_THREADS 27
#define GRID_SIZE 9

typedef struct {
    int row;
    int column;
} parameters;

extern int sudoku[GRID_SIZE][GRID_SIZE];
extern int validation_results[NUM_THREADS];

// Function declarations for threads
void *validate_row(void *param);
void *validate_column(void *param);
void *validate_subgrid(void *param);

#endif // VALIDATOR_H
