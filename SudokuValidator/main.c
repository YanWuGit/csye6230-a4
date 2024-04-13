

int main()
{
    // Declare array to hold results
    int results[NUM_THREADS] = {0};

    // Declare an array of threads
    pthread_t threads[NUM_THREADS];

    // Create 9 threads for checking rows
    for (int i = 0; i < GRID_SIZE; i++)
    {
        parameters *data = (parameters *)malloc(sizeof(parameters));
        data->row = i;
        data->column = 0; // start column is irrelevant for row validation
        pthread_create(&threads[i], NULL, validate_row, (void *)data);
    }

    // Similarly, create threads for checking columns and subgrids

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Check results
    for (int i = 0; i < NUM_THREADS; i++)
    {
        if (results[i] == 0)
        {
            printf("Sudoku puzzle is invalid.\n");
            return EXIT_FAILURE;
        }
    }

    printf("Sudoku puzzle is valid.\n");
    return EXIT_SUCCESS;
}
