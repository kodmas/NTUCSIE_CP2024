#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define MAX_N 30
#define MAX_BUDGET 500000
 
int Reach[MAX_N];
int Cost[MAX_N];
 
// Function to compute paths from a specific index to N-1
int dfs(int start, int current, int remaining_budget, int N) {
    if (current == N - 1) {
        return 1; // Successfully reached the target
    }
    if (remaining_budget < 0) {
        return 0; // Budget exhausted
    }
 
    int paths = 0;
    for (int jump = 1; jump <= Reach[current]; jump++) {
        int next = current + jump;
        if (next < N && remaining_budget >= Cost[next]) {
            paths += dfs(start, next, remaining_budget - Cost[next], N);
        }
    }
    return paths;
}
 
int main() {
    int N, budget;
    scanf("%d", &N);
 
    for (int i = 0; i < N; i++) {
        scanf("%d", &Reach[i]);
    }
 
    for (int i = 0; i < N; i++) {
        scanf("%d", &Cost[i]);
    }
 
    scanf("%d", &budget);
 
    // Compute paths for each index to N-1
    for (int i = 0; i < N - 1; i++) {
        int remaining_budget = budget - Cost[i];
        if (remaining_budget < 0) {
            printf("0\n"); // If starting budget is insufficient
            continue;
        }
        printf("%d\n", dfs(i, i, remaining_budget, N));
    }
 
    return 0;
}