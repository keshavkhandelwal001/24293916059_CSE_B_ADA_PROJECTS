#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binarysearch(int arr[], int n, int key) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] == key) {
            return mid;  // Element found
        } else if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;  // Element not found
}

int main() {
    int n_values[5];

    printf("Enter 5 array sizes:\n");
    for (int i = 0; i < 5; i++) {
        printf("n[%d]: ", i + 1);
        scanf("%d", &n_values[i]);
    }

    printf("\n--- Binary Search Performance ---\n");

    for (int i = 0; i < 5; i++) {
        int n = n_values[i];

        // Allocate memory for array
        int *arr = (int *)malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed for n = %d\n", n);
            continue;
        }

        // Fill array with sorted values: 1 to n
        for (int j = 0; j < n; j++) {
            arr[j] = j + 1;
        }

        int key = n;  // Search for the last element (best-case or worst-case depending on binary search)

        clock_t start = clock();
        int result = binarysearch(arr, n, key);
        clock_t end = clock();

        double time_taken = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC; // in milliseconds

        printf("\nArray size: %d\n", n);
        printf("Searching for: %d\n", key);
        if (result != -1) {
            printf("Result: Element found at index %d\n", result);
        } else {
            printf("Result: Element not found\n");
        }
        printf("Time taken: %.5f ms\n", time_taken);

        free(arr);  // Free memory
    }

    return 0;
}









