#include <stdio.h>
#include <stdlib.h>
 
#define MAX_NODES 1000
#define MAX_PATHS 1000
 
// 儲存路徑的結構
typedef struct {
    int nums[MAX_NODES];  // 儲存路徑上的節點索引
    int length;           // 路徑長度
    int head;             // 路徑的頭端節點索引
} Path;
 
int N, S;
int points[MAX_NODES];
Path paths[MAX_PATHS];    // 儲存所有符合條件的路徑
int path[MAX_NODES];      // 當前搜索的路徑
int path_count = 0;
 
// 比較函數，用於排序
int compare_paths(const void* a, const void* b) {
    Path* path_a = (Path*)a;
    Path* path_b = (Path*)b;
 
    // 按頭端索引從大到小排序
    return path_b->head - path_a->head;
}
 
// 儲存當前路徑
void save_path(int start, int end) {
    paths[path_count].length = end - start + 1;
    paths[path_count].head = path[end];  // 儲存頭端索引
    for (int i = end, j = 0; i >= start; i--, j++) {
        paths[path_count].nums[j] = path[i]; // 儲存路徑上的節點索引
    }
    path_count++;
}
 
// 遞迴函數，從節點 index 開始搜索
void dfs(int index, int current_sum, int path_length) {
    // 將當前節點加入路徑
    path[path_length] = index;
    current_sum += points[index];
 
    // 檢查是否為葉節點
    int is_leaf = (2 * index + 1 >= N || points[2 * index + 1] == 0) &&
                 (2 * index + 2 >= N || points[2 * index + 2] == 0);
 
    // 從當前節點回溯檢查路徑是否符合條件
    int sum = 0;
    for (int i = path_length; i >= 0; i--) {
        sum += points[path[i]];
        if (sum == S) {
            save_path(i, path_length);
        }
    }
 
    // 繼續搜索子節點
    if (2 * index + 1 < N && points[2 * index + 1] != 0) {
        dfs(2 * index + 1, current_sum, path_length + 1);
    }
    if (2 * index + 2 < N && points[2 * index + 2] != 0) {
        dfs(2 * index + 2, current_sum, path_length + 1);
    }
}
 
int main() {
    // 讀取輸入
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &points[i]);
    }
    scanf("%d", &S);
 
    // 從根節點開始搜索
    if (points[0] != 0) {
        dfs(0, 0, 0);
    }
 
    // 按頭端索引排序所有路徑
    qsort(paths, path_count, sizeof(Path), compare_paths);
 
    // 輸出路徑數量
    printf("%d\n", path_count);
 
    // 按排序後的順序輸出所有路徑
    for (int i = path_count-1; i >= 0; i--) {
        for (int j = 0; j < paths[i].length; j++) {
            printf("%d", points[paths[i].nums[j]]); // 根據索引輸出實際值
            if (j < paths[i].length - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
 
    return 0;
}