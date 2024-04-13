#include "validator.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int main(int argc, char *argv[]) {
    // Check command-line arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Read the Sudoku puzzle from the specified file
    if (!read_puzzle_from_file(argv[1], sudoku)) {
        fprintf(stderr, "Failed to load Sudoku puzzle from file.\n");
        return EXIT_FAILURE;
    }

    // Declare an array of threads
    pthread_t threads[NUM_THREADS];
    int threadIndex = 0;

    // Create threads for checking rows
    for (int i = 0; i < GRID_SIZE; i++) {
        parameters *data = (parameters *)malloc(sizeof(parameters));
        data->row = i;
        data->column = 0; // Column is irrelevant for row validation
        pthread_create(&threads[threadIndex++], NULL, validate_row, (void *)data);
    }

    // Create threads for checking columns
    for (int i = 0; i < GRID_SIZE; i++) {
        parameters *data = (parameters *)malloc(sizeof(parameters));
        data->row = 0; // Row is irrelevant for column validation
        data->column = i;
        pthread_create(&threads[threadIndex++], NULL, validate_column, (void *)data);
    }

    // Create threads for checking 3x3 subgrids
    for (int i = 0; i < GRID_SIZE; i += 3) {
        for (int j = 0; j < GRID_SIZE; j += 3) {
            parameters *data = (parameters *)malloc(sizeof(parameters));
            data->row = i;
            data->column = j;
            pthread_create(&threads[threadIndex++], NULL, validate_subgrid, (void *)data);
        }
    }


    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Check results
    for (int i = 0; i < NUM_THREADS; i++) {
        if (validation_results[i] == 0) {
            printf("thread: %d is invalid.\n", i);
            printf("Sudoku puzzle is invalid.\n");
            return EXIT_FAILURE;
        }
    }

    printf("Sudoku puzzle is valid.\n");
    return EXIT_SUCCESS;
}
