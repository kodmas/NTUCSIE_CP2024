#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 10

// Define piece types
#define EMPTY 0
#define BISHOP 3
#define ROOK 4
#define QUEEN 5
#define KING 6
#define OBSTACLE 7

// Movement direction arrays
int dx[] = {-1, -1, 1, 1, -1, 0, 1, 0}; // Bishop and Queen
int dy[] = {-1, 1, -1, 1, 0, -1, 0, 1}; // Bishop and Queen
int rx[] = {-1, 0, 1, 0}; // Rook and Queen
int ry[] = {0, -1, 0, 1}; // Rook and Queen

int n, board[MAX_N][MAX_N], startX, startY, minSteps = INT_MAX;
int pieceCount; // To keep track of remaining pieces

// Function to check if a coordinate is within board bounds
int check(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < n);
}

// Function to reset the visited flag array
int visited[MAX_N][MAX_N];
void init() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            visited[i][j] = 0;
        }
    }
}

// Function to calculate the number of pieces on the board
void countPieces() {
    pieceCount = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] != EMPTY && board[i][j] != OBSTACLE) {
                pieceCount++;
            }
        }
    }
}

// Depth-First Search function
void DFS(int x, int y, int steps, int currentPiece) {
    // Debugging output
    printf("DFS called with (x=%d, y=%d, steps=%d, piece=%d, pieceCount=%d)\n", x, y, steps, currentPiece, pieceCount); 

    // Pruning: If current steps + remaining pieces - 1 >= minSteps, terminate
    if (steps + pieceCount - 1 >= minSteps) {
        printf("Pruning at (x=%d, y=%d, steps=%d)\n", x, y, steps);
        return;
    }

    // If only one piece remains, update minSteps and end the search
    if (pieceCount == 1) {
        minSteps = steps;
        printf("Found solution with %d steps\n", steps);
        return;
    }

    visited[x][y] = 1;

    // Based on the current piece type, determine the position after movement
    switch (currentPiece) {
        case BISHOP:
            for (int i = 0; i < 4; i++) {
                int newX = x + dx[i];
                int newY = y + dy[i];
                while (check(newX, newY) && board[newX][newY] != OBSTACLE && (board[newX][newY] == EMPTY || visited[newX][newY])) {
                    newX += dx[i];
                    newY += dy[i];
                }
                if (check(newX, newY) && board[newX][newY] != OBSTACLE && !visited[newX][newY]) {
                    int capturedPiece = board[newX][newY];
                    board[newX][newY] = EMPTY; 
                    pieceCount--;

                    // Debugging output before recursive call
                    printf("Moving Bishop from (%d, %d) to (%d, %d), capturing %d\n", x, y, newX, newY, capturedPiece);

                    DFS(newX, newY, steps + 1, capturedPiece);
                    board[newX][newY] = capturedPiece; // Backtrack
                    pieceCount++;

                    // Debugging output after recursive call
                    printf("Backtracking Bishop from (%d, %d) to (%d, %d)\n", newX, newY, x, y);

                    // Reset visited for this move
                    while (newX != x || newY != y) {  
                        visited[newX][newY] = 0;
                        newX -= dx[i];
                        newY -= dy[i];
                    }
                }
            }
            break;

        case ROOK:
            for (int i = 0; i < 4; i++) {
                int newX = x + rx[i];
                int newY = y + ry[i];
                while (check(newX, newY) && board[newX][newY] != OBSTACLE && (board[newX][newY] == EMPTY || visited[newX][newY])) {
                    newX += rx[i];
                    newY += ry[i];
                }
                if (check(newX, newY) && board[newX][newY] != OBSTACLE && !visited[newX][newY]) {
                    int capturedPiece = board[newX][newY];
                    board[newX][newY] = EMPTY; 
                    pieceCount--;

                    // Debugging output before recursive call
                    printf("Moving Rook from (%d, %d) to (%d, %d), capturing %d\n", x, y, newX, newY, capturedPiece);

                    DFS(newX, newY, steps + 1, capturedPiece);
                    board[newX][newY] = capturedPiece; // Backtrack
                    pieceCount++;

                    // Debugging output after recursive call
                    printf("Backtracking Rook from (%d, %d) to (%d, %d)\n", newX, newY, x, y);

                    // Reset visited for this move
                    while (newX != x || newY != y) {  
                        visited[newX][newY] = 0;
                        newX -= rx[i];
                        newY -= ry[i];
                    }
                }
            }
            break;

        case QUEEN:
            for (int i = 0; i < 8; i++) {
                int newX = x + dx[i];
                int newY = y + dy[i];
                while (check(newX, newY) && board[newX][newY] != OBSTACLE && (board[newX][newY] == EMPTY || visited[newX][newY])) {
                    newX += dx[i];
                    newY += dy[i];
                }
                if (check(newX, newY) && board[newX][newY] != OBSTACLE && !visited[newX][newY]) {
                    int capturedPiece = board[newX][newY];
                    board[newX][newY] = EMPTY; 
                    pieceCount--;

                    // Debugging output before recursive call
                    printf("Moving Queen from (%d, %d) to (%d, %d), capturing %d\n", x, y, newX, newY, capturedPiece);

                    DFS(newX, newY, steps + 1, capturedPiece);
                    board[newX][newY] = capturedPiece; // Backtrack
                    pieceCount++;

                    // Debugging output after recursive call
                    printf("Backtracking Queen from (%d, %d) to (%d, %d)\n", newX, newY, x, y);

                    // Reset visited for this move
                    while (newX != x || newY != y) {  
                        visited[newX][newY] = 0;
                        newX -= dx[i];
                        newY -= dy[i];
                    }
                }
            }
            break;

        case KING:
            for (int i = 0; i < 8; i++) {
                int newX = x + dx[i];
                int newY = y + dy[i];
                if (check(newX, newY) && board[newX][newY] != OBSTACLE && !visited[newX][newY]) {
                    int capturedPiece = board[newX][newY];
                    board[newX][newY] = EMPTY; 
                    pieceCount--;

                    // Debugging output before recursive call
                    printf("Moving King from (%d, %d) to (%d, %d), capturing %d\n", x, y, newX, newY, capturedPiece);

                    DFS(newX, newY, steps + 1, capturedPiece);
                    board[newX][newY] = capturedPiece; // Backtrack
                    pieceCount++;

                    // Debugging output after recursive call
                    printf("Backtracking King from (%d, %d) to (%d, %d)\n", newX, newY, x, y);

                    // Reset visited for this move (King's move is one step)
                    visited[newX][newY] = 0; 
                }
            }
            break;
    }

    visited[x][y] = 0; // Backtrack for the current position
}

int main() {
    // Read input data
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &board[i][j]);
        }
    }
    scanf("%d %d", &startX, &startY);

    // Initialize and count pieces
    init();
    countPieces();

    // Call DFS to get the minimum steps
    DFS(startX, startY, 0, board[startX][startY]);

    // Output the result
    printf("%d\n", minSteps);

    return 0;
}