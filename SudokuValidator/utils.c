#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

// Reads a Sudoku puzzle from a file
bool read_puzzle_from_file(const char* filename, int puzzle[GRID_SIZE][GRID_SIZE]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Cannot open file %s\n", filename);
        return false;
    }

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (fscanf(file, "%d", &puzzle[i][j]) != 1) {
                fprintf(stderr, "Error reading puzzle from file.\n");
                fclose(file);
                return false;
            }
        }
    }

    fclose(file);
    return true;
}

// Prints the Sudoku puzzle to stdout
void print_puzzle(int puzzle[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%d ", puzzle[i][j]);
        }
        printf("\n");
    }
}
