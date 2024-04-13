#include "validator.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int sudoku[GRID_SIZE][GRID_SIZE];
int validation_results[NUM_THREADS];

// Helper function to check if all elements in an array are unique
int are_elements_unique(int elements[], int length) {
    int checker[GRID_SIZE + 1] = {0}; // Tracker for digits 1-9

    for (int i = 0; i < length; i++) {
        if (elements[i] < 1 || elements[i] > GRID_SIZE) {
            // Element out of valid range (1-9)
            return 0;
        }
        if (checker[elements[i]] == 1) {
            // Duplicate found
            return 0;
        }
        checker[elements[i]] = 1; // Mark digit as found
    }
    return 1; // All elements are unique
}

// Thread function to validate a single row
void *validate_row(void *param) {
    parameters *p = (parameters *)param;
    int row[GRID_SIZE];

    printf("checking row %d\n", p->row);
    // Copy the row into a local array
    for (int i = 0; i < GRID_SIZE; i++) {
        row[i] = sudoku[p->row][i];
    }

    // Check if the row contains unique elements 1-9
    validation_results[p->row] = are_elements_unique(row, GRID_SIZE);

    // Free the allocated memory for parameters
    free(param);

    pthread_exit(NULL);
}

// Thread function to validate a single column
void *validate_column(void *param) {
    parameters *p = (parameters *)param;
    int col[GRID_SIZE];

    printf("checking column %d\n", p->column);
    // Copy the column into a local array
    for (int i = 0; i < GRID_SIZE; i++) {
        col[i] = sudoku[i][p->column];
    }

    // Check if the column contains unique elements 1-9
    validation_results[GRID_SIZE + p->column] = are_elements_unique(col, GRID_SIZE);

    // Free the allocated memory for parameters
    free(param);

    pthread_exit(NULL);
}

// Thread function to validate a single 3x3 subgrid
void *validate_subgrid(void *param) {
    parameters *p = (parameters *)param;
    int subgrid[GRID_SIZE];
    int index = 0;

    // Calculate the starting row and column for the 3x3 subgrid
    int startRow = p->row;
    int startCol = p->column;

    printf("checking 3x3 subgrid starting at %d, %d\n", startRow, startCol);
    // Copy the subgrid into a local array
    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            subgrid[index++] = sudoku[i][j];
        }
    }

    // Check if the subgrid contains unique elements 1-9
    validation_results[2 * GRID_SIZE + (p->row / 3) * 3 + (p->column / 3)] = are_elements_unique(subgrid, GRID_SIZE);

    // Free the allocated memory for parameters
    free(param);

    pthread_exit(NULL);
}
