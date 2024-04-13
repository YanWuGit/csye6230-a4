#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10 // Size of the array
int array[SIZE] = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8};

// Function declarations
void *sort(void *params);
void *merge(void *params);
void quicksort(int left, int right);
void mergeArrays(int left, int mid, int right);

// Structure for passing data to threads
typedef struct
{
    int left;
    int right;
} parameters;

int main()
{
    int mid = SIZE / 2;

    // Creating parameters for the sorting threads
    parameters *data1 = (parameters *)malloc(sizeof(parameters));
    parameters *data2 = (parameters *)malloc(sizeof(parameters));
    data1->left = 0;
    data1->right = mid - 1;
    data2->left = mid;
    data2->right = SIZE - 1;

    // Thread identifiers
    pthread_t sortingThread1, sortingThread2, mergingThread;

    // Creating sorting threads
    pthread_create(&sortingThread1, NULL, sort, data1);
    pthread_create(&sortingThread2, NULL, sort, data2);

    // Waiting for sorting threads to finish
    pthread_join(sortingThread1, NULL);
    pthread_join(sortingThread2, NULL);

    // Merging the two halves
    pthread_create(&mergingThread, NULL, merge, data1);
    pthread_join(mergingThread, NULL);

    // Output the sorted array
    printf("Sorted Array: ");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Free allocated memory
    free(data1);
    free(data2);

    return 0;
}

// Thread function to sort a part of the array
void *sort(void *params)
{
    parameters *p = (parameters *)params;
    quicksort(p->left, p->right);
    pthread_exit(0);
}

// Thread function to merge two sorted parts of the array
void *merge(void *params)
{
    parameters *p = (parameters *)params;
    mergeArrays(p->left, (p->left + p->right) / 2, p->right);
    pthread_exit(0);
}

// Quicksort algorithm
void quicksort(int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int pivot = array[left];
    int l = left;
    int r = right;
    int temp;

    while (l < r)
    {
        while (array[r] > pivot)
        {
            r--;
        }
        while (l < r && array[l] <= pivot)
        {
            l++;
        }
        temp = array[l];
        array[l] = array[r];
        array[r] = temp;
    }

    array[left] = array[l];
    array[l] = pivot;

    quicksort(left, l - 1);
    quicksort(l + 1, right);
}

// Function to merge two sorted halves of the array into a single sorted array
void mergeArrays(int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    // Merge the temp arrays back into array[left..right]
    i = 0;    // Initial index of first subarray
    j = 0;    // Initial index of second subarray
    k = left; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            array[k] = L[i];
            i++;
        }
        else
        {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        array[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2)
    {
        array[k] = R[j];
        j++;
        k++;
    }
}
