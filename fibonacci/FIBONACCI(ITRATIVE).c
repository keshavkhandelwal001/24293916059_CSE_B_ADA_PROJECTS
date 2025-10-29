#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Recursive Fibonacci function
int recursive_fibonacci(int n) {
    if (n < 0)
        return -1; // invalid input
    else if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return recursive_fibonacci(n - 1) + recursive_fibonacci(n - 2);
}

int main() {
    int *n_values;      // Array to store input values
    int *results;       // Array to store Fibonacci results
    double *times;      // Array to store computation times
    int i;

    // Allocate memory for 5 integers
    n_values = (int *)malloc(5 * sizeof(int));
    results = (int *)malloc(5 * sizeof(int));
    times = (double *)malloc(5 * sizeof(double));

    if (n_values == NULL || results == NULL || times == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter 5 different values of n:\n");
    for (i = 0; i < 5; i++) {
        printf("n[%d] = ", i + 1);
        if (scanf("%d", &n_values[i]) != 1) {
            printf("Invalid input!\n");
            free(n_values);
            free(results);
            free(times);
            return 1;
        }
    }

    for (i = 0; i < 5; i++) {
        clock_t start, end;
        start = clock();

        results[i] = recursive_fibonacci(n_values[i]);

        end = clock();
        times[i] = ((double)(end - start)) / CLOCKS_PER_SEC;
    }

    printf("\nResults:\n");
    for (i = 0; i < 5; i++) {
        if (results[i] >= 0)
            printf("Fibonacci(%d) = %d \t Time: %.6f seconds\n", 
                    n_values[i], results[i], times[i]);
        else
            printf("Fibonacci(%d) = Invalid input\n", n_values[i]);
    }

    // Free allocated memory
    free(n_values);
    free(results);
    free(times);

    return 0;
}
