#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_N 100

char target[MAX_N + 1];
int board[MAX_N][MAX_N];
int n, l;
int min_distance = INT_MAX;

// Function to print the current path
// void print_path(int path[], int index) {
//     printf("Path: ");
//     for (int i = 0; i < index; i++) {
//         printf("%d", path[i]);
//     }
//     printf("\n");
// }

// Recursive function to explore all possible paths with incremental distance calculation
void dfs(int row, int col, int index, int current_distance, int path[]) {
    // Early exit if current distance already exceeds the minimum found
    if (current_distance >= min_distance) {
        return;
    }

    // Base case: if path length is exactly l, update the minimum distance if needed
    if (index == l) {
        // print_path(path, index); // Print path for debugging
        if (current_distance < min_distance) {
            min_distance = current_distance;
        }
        return;
    }

    // Calculate the incremental distance on the way
    int next_distance = current_distance;
    if (board[row][col] + '0' != target[index]) { // Convert board value to char and compare
        next_distance |= 1 << (l - index - 1);    // Set the bit for this index if different
    }

    // Record the current cell in the path
    path[index] = board[row][col];

    // Temporarily mark the cell as visited for this path
    // visited[row][col] = 1;

    // Explore adjacent cells if within bounds
    if (row > 0) { // Up
        dfs(row - 1, col, index + 1, next_distance, path);
    }
    if (row < n - 1) { // Down
        dfs(row + 1, col, index + 1, next_distance, path);
    }
    if (col > 0) { // Left
        dfs(row, col - 1, index + 1, next_distance, path);
    }
    if (col < n - 1) { // Right
        dfs(row, col + 1, index + 1, next_distance, path);
    }

    // Backtrack: unmark the cell to allow revisiting in a different path
    // visited[row][col] = 0;
}

int main() {
    // Input reading
    scanf("%d %d", &n, &l);
    scanf("%s", target);

    // Read the board with spaces between numbers
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &board[i][j]);
        }
    }

    int path[MAX_N];                   // To store the current path

    // Start DFS from every cell in the board
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dfs(i, j, 0, 0, path); // Start DFS from cell (i, j)

            // Early exit if minimum distance is 0, as we can't do better
            if (min_distance == 0) {
                printf("%d", min_distance);
                return 0;
            }
        }
    }

    // Output the minimum distance found
    printf("%d", min_distance);
    return 0;
}
