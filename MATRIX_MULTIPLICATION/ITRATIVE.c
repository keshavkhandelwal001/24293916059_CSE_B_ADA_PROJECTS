#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to multiply matrices
void multiply_matrices(int n, int **A, int **B, int **C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function to allocate a 2D matrix dynamically
int **allocate_matrix(int n) {
    int **matrix = malloc(n * sizeof(int *));
    if (!matrix) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(n * sizeof(int));
        if (!matrix[i]) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

// Function to free a 2D matrix
void free_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int sizes[] = {100, 200, 300, 400, 500, 600, 700};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    srand(time(NULL));

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        printf("\nMatrix size: %d x %d\n", n, n);

        int **A = allocate_matrix(n);
        int **B = allocate_matrix(n);
        int **C = allocate_matrix(n);

        // Fill A and B with random numbers
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
            }
        }

        clock_t start = clock();
        multiply_matrices(n, A, B, C);
        clock_t end = clock();

        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Execution time: %.6f seconds\n", time_taken);

        // Free memory
        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C, n);
    }

    return 0;
}
