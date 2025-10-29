 #include <stdio.h>
#include <time.h>

#define ITERATIONS 100000

// Bottom-Up Fibonacci Function
unsigned long long int fibonacci(int n) {
    if (n <= 1)
        return n;

    unsigned long long int fib[n + 1];
    fib[0] = 0;
    fib[1] = 1;

    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    return fib[n];
}

int main() {
    int n[] = {10, 15,  25, 30};

    for (int i = 0; i < 5; i++) {
        unsigned long long int result = 0;

        clock_t start_time = clock();

        for (int j = 0; j < ITERATIONS; j++) {
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
