#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct Activity {
    int start;
    int finish;
};
int compare(const void *a, const void *b) {
    struct Activity *A = (struct Activity *)a;
    struct Activity *B = (struct Activity *)b;
    return A->finish - B->finish;
}


void activitySelection(struct Activity activities[], int n) {

    qsort(activities, n, sizeof(struct Activity), compare);

    
    int i = 0;

    
    for (int j = 1; j < n; j++) {
        
        if (activities[j].start >= activities[i].finish) {
            i = j;
        }
    }
}

int main() {
    
    struct Activity activities[] = {
        {1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}, {5, 9},
        {2, 5}, {6, 10}, {8, 11}, {12, 14}, {13, 16}, {15, 18}
    };

    int n = sizeof(activities) / sizeof(activities[0]);
    int iterations = 1000;

    clock_t start_time, end_time;
    double total_time = 0.0;

    for (int i = 0; i < iterations; i++) {
        start_time = clock();
        activitySelection(activities, n);
        end_time = clock();

        total_time += (double)(end_time - start_time) / CLOCKS_PER_SEC;
    }

    double avg_time = total_time / iterations;


    printf("Sample Run (Greedy Selection Order by Finish Time):\n");
    qsort(activities, n, sizeof(struct Activity), compare);
    printf("Selected Activities:\n");

    int i = 0;
    printf("A%d -> (Start: %d, Finish: %d)\n", i + 1, activities[i].start, activities[i].finish);
    for (int j = 1; j < n; j++) {
        if (activities[j].start >= activities[i].finish) {
            printf("A%d -> (Start: %d, Finish: %d)\n", j + 1, activities[j].start, activities[j].finish);
            i = j;
        }
    }

    printf("\nAverage Execution Time over %d iterations: %f seconds\n", iterations, avg_time);

    return 0;
}