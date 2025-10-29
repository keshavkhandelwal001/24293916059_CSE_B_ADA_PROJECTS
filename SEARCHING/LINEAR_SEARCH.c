#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linearsearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

int main() {
    // Array of 5 sizes to test
    int sizes[5] = {1000, 5000, 10000, 50000, 100000};

    printf("Linear Search Performance:\n\n");

    for (int i = 0; i < 5; i++) {
        int n = sizes[i];

        // Dynamically allocate memory for array of size n
        int *arr = (int *)malloc(n * sizeof(int));

        // Fill array with values 1 to n
        for (int j = 0; j < n; j++) {
            arr[j] = j + 1;
        }

        int key = n; // Searching for the last element (worst case)

        clock_t start, end;
        start = clock();

        int result = linearsearch(arr, n, key);

        end = clock();

        double time_taken = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;

        printf("Array size: %d\n", n);
        printf("Searching for: %d\n", key);
        if (result != -1) {
            printf("Element found at index: %d\n", result);
        } else {
            printf("Element not found\n");
        }
        printf("Time taken: %.6lf ms\n\n", time_taken);

        free(arr); // Free memory
    }

    return 0;
}
