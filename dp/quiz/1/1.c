#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAX 1000 // Adjust based on constraints

char A[MAX + 1][MAX + 1];
int dp[MAX + 1][MAX + 1];
int vertical[MAX + 1][MAX + 1];
int horizontal[MAX + 1][MAX + 1];
int diagonal[MAX + 1][MAX + 1];

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    // Input grid
    for (int i = 1; i <= m; i++) {
        scanf("%s", A[i] + 1); // Reading row starting from index 1
    }

    // Initialize DP and prefix sums
    memset(dp, 0, sizeof(dp));
    memset(vertical, 0, sizeof(vertical));
    memset(horizontal, 0, sizeof(horizontal));
    memset(diagonal, 0, sizeof(diagonal));

    // Base case
    dp[1][1] = (A[1][1] == '.') ? 1 : 0;
    vertical[1][1] = dp[1][1];
    horizontal[1][1] = dp[1][1];
    diagonal[1][1] = dp[1][1];

    // DP Transition
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (A[i][j] == '#') continue; // Skip blocked points

            // Vertical and Horizontal Contributions
            if (i > 1) {
                dp[i][j] = (dp[i][j] + vertical[i - 1][j]) % MOD;
            }
            if (j > 1) {
                dp[i][j] = (dp[i][j] + horizontal[i][j - 1]) % MOD;
            }
            if (i > 1 && j > 1) {
                dp[i][j] = (dp[i][j] + diagonal[i - 1][j - 1]) % MOD;
            }

            // Update prefix sums
            vertical[i][j] = (vertical[i - 1][j] + dp[i][j]) % MOD;
            horizontal[i][j] = (horizontal[i][j - 1] + dp[i][j]) % MOD;
            diagonal[i][j] = (diagonal[i - 1][j - 1] + dp[i][j]) % MOD;
        }
    }
    
    // Output the result
    printf("%d\n", dp[m][n]);

    return 0;
}
