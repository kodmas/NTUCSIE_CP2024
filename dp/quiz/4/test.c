#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

typedef struct {
    int w, l, h, old;
} Book;

Book books[MAX_N];
int dp[MAX_N];         // Maximum height ending with each book
int bottom[MAX_N];     // Height of the bottommost book for each stack

int main() {
    int n;
    scanf("%d", &n);

    // Read book dimensions
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &books[i].w, &books[i].l, &books[i].h, &books[i].old);
    }

    int max_height = 0;
    int bottom_of_max = 0;

    // Dynamic Programming to find the maximum stack height
    for (int i = 0; i < n; i++) {
        dp[i] = books[i].h;    // Base case: the height of the book itself
        bottom[i] = books[i].h; // Initially, the book is the bottommost

        if (books[i].old == 1) {
            // "Old" books cannot have other books on top
            continue;
        }

        for (int j = 0; j < i; j++) {
            if (books[j].w < books[i].w && books[j].l < books[i].l) {
                if (dp[j] + books[i].h > dp[i]) {
                    dp[i] = dp[j] + books[i].h;
                    bottom[i] = bottom[j]; // Propagate the bottom book's height
                }
            }
        }

        // Update the global maximum and the corresponding bottom book
        if (dp[i] > max_height) {
            max_height = dp[i];
            bottom_of_max = bottom[i];
        }
    }

    // Output results
    printf("%d\n", max_height);
    printf("%d\n", bottom_of_max);

    return 0;
}
