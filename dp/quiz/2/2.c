#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_M 100
#define MAX_N 100
#define INF -1e9 // Represents an invalid state

double dp[MAX_M][MAX_N][3]; // DP array: max battery at each cell with direction
int grid[MAX_M][MAX_N];

double max(double a, double b) {
    return (a > b) ? a : b;
}

int main() {
    int m, n, B, B_max;
    scanf("%d %d %d %d", &m, &n, &B, &B_max);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    // Initialize DP array
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int d = 0; d < 3; d++) {
                dp[i][j][d] = INF;
            }
        }
    }

    // Initial state
    dp[0][0][0] = dp[0][0][1] = dp[0][0][2] = B;

    // DP transitions
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int d = 0; d < 3; d++) { // Current direction
                if (dp[i][j][d] == INF) continue;

                // Battery after recharging or cost adjustment
                double battery = dp[i][j][d] + grid[i][j];
                if (battery > B_max) battery = B_max;

                // Move right
                if (j + 1 < n) {
                    double cost = 1; // Basic movement cost
                    if (d == 1) cost += 0.5; // Left-turn penalty
                    if (d == 2) cost += 0.2; // Right-turn penalty

                    if (battery >= cost) {
                        dp[i][j + 1][0] = max(dp[i][j + 1][0], battery - cost);
                    }
                }

                // Move down
                if (i + 1 < m) {
                    double cost = 1; // Basic movement cost
                    if (d == 0) cost += 0.2; // Right-turn penalty
                    if (d == 2) cost += 0.5; // Left-turn penalty

                    if (battery >= cost) {
                        dp[i + 1][j][1] = max(dp[i + 1][j][1], battery - cost);
                    }
                }

                // Move diagonally
                if (i + 1 < m && j + 1 < n) {
                    double cost = 1; // Basic movement cost
                    if (d == 0) cost += 0.2; // Right-turn penalty
                    if (d == 1) cost += 0.5; // Left-turn penalty

                    if (battery >= cost) {
                        dp[i + 1][j + 1][2] = max(dp[i + 1][j + 1][2], battery - cost);
                    }
                }
            }
        }
    }

    // Find the maximum battery at the destination
    double result = max(dp[m - 1][n - 1][0], max(dp[m - 1][n - 1][1], dp[m - 1][n - 1][2]));

    // Output the result
    if (result == INF) {
        printf("-1\n");
    } else {
        printf("%.1f\n", result);
    }

    return 0;
}
