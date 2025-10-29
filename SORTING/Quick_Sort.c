#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int sizes[] = {500, 1000, 1500, 2000, 2500, 3000, 3500};
    int numTests = 7;
    int n, i;
    clock_t start, end;
    double cpu_time_used;
    srand(time(0));

    for (int t = 0; t < numTests; t++) {
        n = sizes[t];
        int *arr = (int*)malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }

        // Generate random numbers
        for (i = 0; i < n; i++) {
            arr[i] = rand() % 10000;
        }

        // Measure sorting time
        start = clock();
        quickSort(arr, 0, n - 1);
        end = clock();

        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
        printf("Time taken for %d elements: %.3f ms\n", n, cpu_time_used);

        free(arr);
    }

    return 0;
}
