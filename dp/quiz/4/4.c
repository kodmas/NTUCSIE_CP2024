#include <stdio.h>
#include <stdlib.h>

#define MAX_N 40001

typedef struct {
    int w, l, h, old_index;
} Book;

Book books[MAX_N];
long dp[MAX_N];         // Maximum height ending with each book
long bottom[MAX_N];     
long bottom_heights[MAX_N]; // Heights of bottom books contributing to max height
long bottom_count = 0;      // Count of top heights

int main() {
    int n;
    scanf("%d", &n);

    // Read book dimensions
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &books[i].w, &books[i].l, &books[i].h, &books[i].old_index);
    }

    long max_height = 0;

    // Dynamic Programming to find the maximum stack height
    for (int i = 0; i < n; i++) {
        dp[i] = books[i].h; // Base case: the height of the book itself
        bottom[i] = books[i].h;
        if(books[i].old_index == 1) continue;
        for (int j = 0; j < i; j++) {
            if (books[j].w < books[i].w && books[j].l < books[i].l) {
                if(dp[j] + books[i].h > dp[i]){
                    dp[i] = dp[j] + books[i].h;
                }
            }
        }
        max_height = max_height > dp[i] ? max_height : dp[i];
    }

    // for(int i=0;i<n;i++){
    //     if(dp[i] == max_height){
    //         for(int j=0;j<n;j++){
    //             if(books[j].old_index == 1){
                    
    //             }
    //         }
    //     }
    // }

    // Collect all valid bottom book heights
    for (int i = 0; i < n; i++) {
        if (dp[i] == max_height) {
            bottom_heights[bottom_count++] = bottom[i];
        }
    }

    // // Sort bottom_heights to output in ascending order
    // for (int i = 0; i < bottom_count - 1; i++) {
    //     for (int j = 0; j < bottom_count - i - 1; j++) {
    //         if (bottom_heights[j] > bottom_heights[j + 1]) {
    //             int temp = bottom_heights[j];
    //             bottom_heights[j] = bottom_heights[j + 1];
    //             bottom_heights[j + 1] = temp;
    //         }
    //     }
    // }

    // for(int i=0;i<n;i++){
    //     printf("%ld ", dp[i]);
    // }
    // printf("\n");

    // for(int i=0;i<n;i++){
    //     printf("%ld ", bottom[i]);
    // }
    // printf("\n");

    // for(int i=0;i<n;i++){
    //     printf("%ld ", bottom_heights[i]);
    // }
    // printf("\n");

    // Output results
    printf("%ld\n", max_height);
    for (int i = 0; i < bottom_count; i++) {
        if (i == 0 || bottom_heights[i] != bottom_heights[i - 1]) { // Avoid duplicates
            printf("%ld\n", bottom_heights[i]);
        }
    }

    return 0;
}
