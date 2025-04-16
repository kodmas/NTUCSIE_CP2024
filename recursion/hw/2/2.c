#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 1001  // Increase size to 1001 to accommodate 1-based indexing

// Adjacency matrix representation
int graph[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];

// DFS to mark all reachable vertices from `v`
void dfs(int v, int n) {
    visited[v] = 1;
    for (int i = 1; i <= n; i++) {  // Adjust loop to 1-based indexing
        if (graph[v][i] && !visited[i]) {
            dfs(i, n);
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // Initialize graph and visited array
    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
        for (int j = 1; j <= n; j++) {
            graph[i][j] = 0;
        }
    }

    // Read edges
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    // Count connected components (blocks)
    int blockCount = 0;
    for (int i = 1; i <= n; i++) {  // Adjust loop to 1-based indexing
        if (!visited[i]) {
            dfs(i, n);
            blockCount++;
        }
    }

    printf("%d", blockCount);
    return 0;
}
