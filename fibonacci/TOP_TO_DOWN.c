#include <stdio.h>
#include <time.h>     

#define MAX 100
#define ITERATIONS 100000

long long int memo[MAX];

void initialize_memo() {
    for (int i = 0; i < MAX; i++) {
        memo[i] = -1;
    }
       }

unsigned long long int fibonacci(int n) {
    if (memo[n] != -1)
        return memo[n];

    if (n <= 1)
        memo[n] = n;
    else
        memo[n] = fibonacci(n - 1) + fibonacci(n - 2);

    return memo[n];
}

int main() {
    int n[] = {10, 15, 20, 25, 30};

    for (int i = 0; i < 5; i++) {
        unsigned long long int result = 0;

        clock_t start_time = clock();

        for (int j = 0; j < ITERATIONS; j++) {
            initialize_memo();  
            result = fibonacci(n[i]);
        }

        clock_t end_time = clock();

        double total_time_ms = ((double)(end_time - start_time) * 1000) / CLOCKS_PER_SEC;
        double avg_time_ms = total_time_ms / ITERATIONS;

        printf("Fibonacci(%d) = %llu\tAverage time over %d runs: %.6f ms\n",
               n[i], result, ITERATIONS, avg_time_ms);
    }

    return 0;
}

