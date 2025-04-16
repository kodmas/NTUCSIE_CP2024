#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define INF -1.0

typedef struct {
    int x, y, battery;
} State;

typedef struct {
    State *data;
    int front, rear, size;
} Queue;

void push(Queue *q, int x, int y, int battery) {
    q->data[q->rear++] = (State){x, y, battery};
}

State pop(Queue *q) {
    return q->data[q->front++];
}

int is_empty(Queue *q) {
    return q->front == q->rear;
}

int directions[3][2] = {
    {0, 1},   // Right
    {1, 0},   // Down
    {1, 1}    // Diagonal
};

int main() {
    int m, n, B, B_max;
    scanf("%d %d %d %d", &m, &n, &B, &B_max);

    // Dynamically allocate grid memory
    int **grid = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        grid[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    // Dynamically allocate dp memory
    double **dp = (double **)malloc(m * sizeof(double *));
    for (int i = 0; i < m; i++) {
        dp[i] = (double *)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            dp[i][j] = INF;
        }
    }

    // Initialize the queue
    Queue q = {malloc(m * n * (B_max + 1) * sizeof(State)), 0, 0, m * n * (B_max + 1)};

    // Base case
    dp[0][0] = B + grid[0][0];
    if (dp[0][0] > B_max) dp[0][0] = B_max;
    push(&q, 0, 0, dp[0][0]);

    // BFS
    while (!is_empty(&q)) {
        State curr = pop(&q);
        int x = curr.x, y = curr.y, battery = curr.battery;

        for (int d = 0; d < 3; d++) {
            int nx = x + directions[d][0];
            int ny = y + directions[d][1];

            if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                int new_battery = battery - 1 + grid[nx][ny];
                if (new_battery < 0) continue; // Skip invalid moves
                if (new_battery > B_max) new_battery = B_max;

                if (new_battery > dp[nx][ny]) {
                    dp[nx][ny] = new_battery;
                    push(&q, nx, ny, new_battery);
                }
            }
        }
    }

    // Output the result
    if (dp[m-1][n-1] == INF) {
        printf("-1\n");
    } else {
        printf("%.1f\n", dp[m-1][n-1]);
    }

    // Free memory
    for (int i = 0; i < m; i++) {
        free(grid[i]);
        free(dp[i]);
    }
    free(grid);
    free(dp);
    free(q.data);

    return 0;
}
