#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INITIAL_PATH_CAPACITY 100
#define MAX_PATH_LENGTH (int)(log2(10000000 + 1)) // Assuming max N = 100000

int path_capacity = INITIAL_PATH_CAPACITY;
int path_count = 0;
int** paths_found = NULL;

void find(int* arr, int N, int S, int index, int* path, int path_len) {
    if (index >= N || arr[index] == 0) return;

    path[path_len] = index; // Store the index directly
    path_len++;
    S -= arr[index];

    if (S == 0) {
        // Resize paths_found if necessary
        if (path_count >= path_capacity) {
            path_capacity *= 2;
            paths_found = (int**)realloc(paths_found, path_capacity * sizeof(int*));
            for (int i = path_count; i < path_capacity; i++) {
                paths_found[i] = (int*)malloc((MAX_PATH_LENGTH + 1) * sizeof(int));
            }
        }

        // Store the path in reverse (bottom-up) order
        for (int i = 0; i < path_len; i++) {
            paths_found[path_count][path_len - i - 1] = path[i]; // Store only the index
        }
        paths_found[path_count][path_len] = -1; // Mark the end of the path
        path_count++;
    }

    find(arr, N, S, 2 * index + 1, path, path_len);
    find(arr, N, S, 2 * index + 2, path, path_len);

    S += arr[index];
    path_len--;
}

int compare_paths(const void* a, const void* b) {
    int* path_a = *(int**)a;
    int* path_b = *(int**)b;

    // Directly compare the indices of the bottom nodes (ascending order)
    return path_a[0] - path_b[0];
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

    paths_found = (int**)malloc(INITIAL_PATH_CAPACITY * sizeof(int*));
    for (int i = 0; i < INITIAL_PATH_CAPACITY; i++) {
        paths_found[i] = (int*)malloc((MAX_PATH_LENGTH + 1) * sizeof(int));
    }

    int* path = (int*)malloc(MAX_PATH_LENGTH * sizeof(int));
    for (int i = 0; i < N; i++) {
        int path_len = 0;
        find(arr, N, S, i, path, path_len);
    }
    free(path);

    qsort(paths_found, path_count, sizeof(int*), compare_paths);

    printf("%d\n", path_count);
    if (path_count > 0) {
        for (int i = 0; i < path_count; i++) {
            int j = 0;
            printf("%d", arr[paths_found[i][j]]); // Access value using the stored index
            j++;
            while (paths_found[i][j] != -1) {
                printf(" %d", arr[paths_found[i][j]]); // Access value using the stored index
                j++;
            }
            printf("\n");
        }
    }
    // Free the dynamically allocated memory for paths_found
    for (int i = 0; i < path_capacity; i++) {
        free(paths_found[i]);
    }
    free(paths_found);
    free(arr);
    return 0;
}