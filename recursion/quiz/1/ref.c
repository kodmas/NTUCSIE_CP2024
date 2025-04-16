#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
 
#define MAX_N 65
#define MAX_L 15
 
int n, l;
char target[MAX_L + 1];
char board[MAX_N][MAX_N];
int minDistance = INT_MAX;
int memo[MAX_N][MAX_N][MAX_L];
 
// 移動方向 (上下左右)
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
 
// 計算密碼距離
int calculateDistance(char *path, int depth) {
    int distance = 0;
    for (int i = 0; i < depth; i++) {
        if (target[i] != path[i]) {
            distance |= (1 << (depth - i - 1));
        }
    }
    return distance;
}
 
// 使用 DFS 探索路徑並更新記憶化表
void dfs(int x, int y, int depth, char *currentPath, int currentDistance) {
    // 提前停止：若當前密碼距離大於等於目前的最小距離
    if (currentDistance >= minDistance) return;
 
    // 更新至目標深度時計算距離
    if (depth == l) {
        minDistance = currentDistance;
        return;
    }
 
    // 若已經有更小的距離存在於 memo 表中，則停止探索
    if (currentDistance >= memo[x][y][depth]) return;
 
    // 更新記憶化表
    memo[x][y][depth] = currentDistance;
 
    // 探索四個方向
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
 
        // 檢查新位置是否在範圍內
        if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
            currentPath[depth] = board[nx][ny];
            int newDistance = calculateDistance(currentPath, depth + 1);
            dfs(nx, ny, depth + 1, currentPath, newDistance);
        }
    }
}
 
int main() {
    // 輸入
    scanf("%d %d", &n, &l);
    scanf("%s", target);
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf(" %c", &board[i][j]);
        }
    }
 
    // 初始化臨時路徑字串，並設置結尾為空字符
    char currentPath[MAX_L + 1];
    currentPath[l] = '\0'; // 結束字元
 
    // 初始化記憶化表格為最大值
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < l; k++) {
                memo[i][j][k] = INT_MAX;
            }
        }
    }
 
    // 從每個起點進行 DFS
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            currentPath[0] = board[i][j];
            int initialDistance = calculateDistance(currentPath, 1);
            dfs(i, j, 1, currentPath, initialDistance);
        }
    }
 
    // 輸出結果
    printf("%d\n", minDistance);
 
    return 0;
}