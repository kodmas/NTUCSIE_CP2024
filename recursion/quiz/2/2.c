#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10001

// Adjacency matrix representation
int graph[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];

// Perform DFS and return the size of the connected component
int dfs(int v, int n) {
    visited[v] = 1;
    int size = 1;  // Start with the current node
    for (int i = 1; i <= n; i++) {
        if (graph[v][i] && !visited[i]) {
            size += dfs(i, n);  // Add the size of each connected component recursively
        }
    }
    return size;
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

    // Count valid blocks (connected components with at least 3 vertices)
    int validBlockCount = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {  // Unvisited node that exists in the graph
            int componentSize = dfs(i, n);
            if (componentSize >= 3) {
                validBlockCount++;
            }
        }
    }

    printf("%d", validBlockCount);
    return 0;
}
