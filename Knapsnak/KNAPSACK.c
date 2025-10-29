#include <stdio.h>
#include <time.h>

#define ITERATIONS 10000

// Function to get max of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// 0/1 Knapsack function using Bottom-Up DP
int knapSack(int capacity, int weight[], int value[], int n) {
    int dp[n+1][capacity+1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weight[i-1] <= w)
                dp[i][w] = max(value[i-1] + dp[i-1][w - weight[i-1]], dp[i-1][w]);
            else
                dp[i][w] = dp[i-1][w];
        }
    }

    return dp[n][capacity];
}

int main() {
    // Sample item values and weights
    int values[] = {60, 100, 120};
    int weights[] = {10, 20, 30};
    int n = sizeof(values) / sizeof(values[0]);

    // Test with 5 different knapsack capacities
    int capacities[] = {10, 20, 30, 40, 50};

    for (int i = 0; i < 5; i++) {
        int capacity = capacities[i];
        int result = 0;

        clock_t start = clock();

        for (int j = 0; j < ITERATIONS; j++) {
            result = knapSack(capacity, weights, values, n);
        }

        clock_t end = clock();

        double total_time = ((double)(end - start) * 1000) / CLOCKS_PER_SEC; // in milliseconds
        double avg_time = total_time / ITERATIONS;

        printf("Capacity = %d\tMax Value = %d\tAverage Time = %.6f ms\n", 
               capacity, result, avg_time);
    }

    return 0;
}
