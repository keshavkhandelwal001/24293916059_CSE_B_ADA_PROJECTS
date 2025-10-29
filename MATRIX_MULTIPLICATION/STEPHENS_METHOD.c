#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int next_power_of_two(int n) {
    int p = 1;
    while (p < n) p *= 2;
    return p;
}

int **alloc_matrix(int n) {
    int **m = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        m[i] = calloc(n, sizeof(int));
    return m;
}

void free_matrix(int **m, int n) {
    for (int i = 0; i < n; i++) free(m[i]);
    free(m);
}

void add_matrix(int n, int **A, int **B, int **C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void sub_matrix(int n, int **A, int **B, int **C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void split_matrix(int n, int **A, int **sub, int row_offset, int col_offset) {
    int k = n / 2;
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            sub[i][j] = A[i + row_offset][j + col_offset];
}

void print_matrix(int n, int **M, const char *name) {
    printf("\n%s:\n", name);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d ", M[i][j]);
        }
        printf("\n");
    }
}

void strassen(int n, int **A, int **B, int **C) {
    if (n <= 2) {  // base case
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                C[i][j] = 0;
                for (int k = 0; k < n; k++)
                    C[i][j] += A[i][k] * B[k][j];
            }
        return;
    }

    int k = n / 2;

    // Allocate submatrices
    int **A11 = alloc_matrix(k), **A12 = alloc_matrix(k);
    int **A21 = alloc_matrix(k), **A22 = alloc_matrix(k);
    int **B11 = alloc_matrix(k), **B12 = alloc_matrix(k);
    int **B21 = alloc_matrix(k), **B22 = alloc_matrix(k);
    int **C11 = alloc_matrix(k), **C12 = alloc_matrix(k);
    int **C21 = alloc_matrix(k), **C22 = alloc_matrix(k);


    int **M1 = alloc_matrix(k), **M2 = alloc_matrix(k), **M3 = alloc_matrix(k);
    int **M4 = alloc_matrix(k), **M5 = alloc_matrix(k), **M6 = alloc_matrix(k), **M7 = alloc_matrix(k);
    int **T1 = alloc_matrix(k), **T2 = alloc_matrix(k);

    // Split A and B
    split_matrix(n, A, A11, 0, 0);
    split_matrix(n, A, A12, 0, k);
    split_matrix(n, A, A21, k, 0);
    split_matrix(n, A, A22, k, k);

    split_matrix(n, B, B11, 0, 0);
    split_matrix(n, B, B12, 0, k);
    split_matrix(n, B, B21, k, 0);
    split_matrix(n, B, B22, k, k);

    // Strassen’s 7 multiplications
    add_matrix(k, A11, A22, T1);
    add_matrix(k, B11, B22, T2);
    strassen(k, T1, T2, M1);

    add_matrix(k, A21, A22, T1);
    strassen(k, T1, B11, M2);

    sub_matrix(k, B12, B22, T1);
    strassen(k, A11, T1, M3);

    sub_matrix(k, B21, B11, T1);
    strassen(k, A22, T1, M4);

    add_matrix(k, A11, A12, T1);
    strassen(k, T1, B22, M5);

    sub_matrix(k, A21, A11, T1);
    add_matrix(k, B11, B12, T2);
    strassen(k, T1, T2, M6);

    sub_matrix(k, A12, A22, T1);
    add_matrix(k, B21, B22, T2);
    strassen(k, T1, T2, M7);

    // Compute C blocks
    add_matrix(k, M1, M4, T1);
    sub_matrix(k, T1, M5, T2);
    add_matrix(k, T2, M7, C11);

    add_matrix(k, M3, M5, C12);

    add_matrix(k, M2, M4, C21);

    sub_matrix(k, M1, M2, T1);
    add_matrix(k, T1, M3, T2);
    add_matrix(k, T2, M6, C22);

    // Combine into C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    // Free all
    free_matrix(A11, k); free_matrix(A12, k); free_matrix(A21, k); free_matrix(A22, k);
    free_matrix(B11, k); free_matrix(B12, k); free_matrix(B21, k); free_matrix(B22, k);
    free_matrix(C11, k); free_matrix(C12, k); free_matrix(C21, k); free_matrix(C22, k);
    free_matrix(M1, k); free_matrix(M2, k); free_matrix(M3, k); free_matrix(M4, k);
    free_matrix(M5, k); free_matrix(M6, k); free_matrix(M7, k);
    free_matrix(T1, k); free_matrix(T2, k);
}

int main() {
    int sizes[] = {63, 150, 200, 300}; 
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    srand(time(NULL));

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int m = next_power_of_two(n); // padded size
        printf("\nOriginal size: %d x %d, Padded size: %d x %d\n", n, n, m, m);

        int **A = alloc_matrix(m);
        int **B = alloc_matrix(m);
        int **C = alloc_matrix(m);

        
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
            }

        clock_t start = clock();
        strassen(m, A, B, C);   
        clock_t end = clock();

        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Execution time (Strassen): %.4f seconds\n", time_taken);


        free_matrix(A, m);
        free_matrix(B, m);
        free_matrix(C, m);
    }

    return 0;
}

