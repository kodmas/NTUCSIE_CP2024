#include <stdio.h>
#include <stdlib.h>

#define MAX_N 40001

typedef struct {
    int w, l, h;
} Book;

Book books[MAX_N];
long dp[MAX_N];         // Maximum height ending with each book
long top_heights[MAX_N]; // Heights of top books contributing to max height
long top_count = 0;      // Count of top heights

int main() {
    int n;
    scanf("%d", &n);

    // Read book dimensions
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &books[i].w, &books[i].l, &books[i].h);
    }

    long max_height = 0;

    // Dynamic Programming to find the maximum stack height
    for (int i = 0; i < n; i++) {
        dp[i] = books[i].h; // Base case: the height of the book itself
        for (int j = 0; j < i; j++) {
            if (books[j].w < books[i].w && books[j].l < books[i].l) {
                dp[i] = dp[i] > dp[j] + books[i].h ? dp[i] : dp[j] + books[i].h;
            }
        }
        max_height = max_height > dp[i] ? max_height : dp[i];
    }

    // Collect all valid topmost book heights
    for (int i = 0; i < n; i++) {
        if (dp[i] == max_height) {
            top_heights[top_count++] = books[i].h;
        }
    }

    // Sort top_heights to output in ascending order
    for (int i = 0; i < top_count - 1; i++) {
        for (int j = 0; j < top_count - i - 1; j++) {
            if (top_heights[j] > top_heights[j + 1]) {
                long temp = top_heights[j];
                top_heights[j] = top_heights[j + 1];
                top_heights[j + 1] = temp;
            }
        }
    }

    // Output results
    printf("%ld", max_height);
    // for (int i = 0; i < top_count; i++) {
    //     if (i == 0 || top_heights[i] != top_heights[i - 1]) { // Avoid duplicates
    //         printf("%d ", top_heights[i]);
    //     }
    // }
    // printf("\n");

    return 0;
}
