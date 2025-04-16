#include <stdio.h>
#include <stdlib.h>

int is_leaf(int* arr, int N, int index) {
    // A node is a leaf if it exists and has no children within bounds
    return arr[index] != 0 && (2 * index + 1 >= N || arr[2 * index + 1] == 0) && 
                              (2 * index + 2 >= N || arr[2 * index + 2] == 0);
}

void find(int* arr, int N, int S, int index, int* path, int path_len, int* path_num) {
    if (index >= N || arr[index] == 0) return;  // Out of bounds or NULL node

    // Add current node to path
    path[path_len] = arr[index];
    path_len++;
    S -= arr[index];  // Update target score

    // Check if leaf node and sum matches target
    if (S == 0 && is_leaf(arr, N, index)) {
        // Print the path from leaf to root
        *path_num += 1;
        for (int i = path_len - 1; i > 0; i--) {
            printf("%d ", path[i]);
        }
        printf("%d\n", path[0]);
    } else {
        // Recurse on left and right child
        find(arr, N, S, 2 * index + 1, path, path_len, path_num);  // Left child
        find(arr, N, S, 2 * index + 2, path, path_len, path_num);  // Right child
    }
}

int main() {
    int N;
    scanf("%d", &N);

    int* arr = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    int S;
    scanf("%d", &S);

    int path_num = 0;

    int* path = (int*)malloc(N * sizeof(int));  // To store the current path
    find(arr, N, S, 0, path, 0, &path_num);

    if(path_num == 0) {
        printf("-1");
    }

    free(arr);
    free(path);
    return 0;
}
