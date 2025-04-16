#include <stdio.h>
#include <stdlib.h>
 
// 最大頂點數
#define MAX_N 10005
 
// 並查集結構
typedef struct {
    int parent;
    int size;
    long long edge_count;
} UnionFind;
 
UnionFind uf[MAX_N];
 
// 初始化並查集
void initialize(int n) {
    for(int i = 0; i <= n; i++) {
        uf[i].parent = i;
        uf[i].size = 1;
        uf[i].edge_count = 0;
    }
}
 
// 查找根節點，並進行路徑壓縮
int find_set(int u) {
    if(uf[u].parent != u) {
        uf[u].parent = find_set(uf[u].parent);
    }
    return uf[u].parent;
}
 
// 合併兩個集合，並更新邊數
void union_set(int u, int v) {
    int pu = find_set(u);
    int pv = find_set(v);
    if(pu != pv) {
        // 合併較小的集合到較大的集合
        if(uf[pu].size < uf[pv].size) {
            int temp = pu;
            pu = pv;
            pv = temp;
        }
        uf[pv].parent = pu;
        uf[pu].size += uf[pv].size;
        uf[pu].edge_count += uf[pv].edge_count + 1;
    }
    else {
        // 同一個集合，僅增加邊數
        uf[pu].edge_count += 1;
    }
}
 
int main() {
    int n, m;
    // 讀取頂點數和邊數
    if(scanf("%d %d", &n, &m) != 2){
        return 0;
    }
 
    initialize(n);
 
    int u, v;
    for(int i = 0; i < m; i++) {
        if(scanf("%d %d", &u, &v) != 2){
            return 0;
        }
        union_set(u, v);
    }
 
    // 用於標記已處理的根節點
    int *seen = (int*)calloc(n + 1, sizeof(int));
    if(seen == NULL){
        return 0;
    }
 
    int special_blocks = 0;
    for(int i = 1; i <= n; i++) {
        int pi = find_set(i);
        if(!seen[pi]) {
            seen[pi] = 1;
            if(uf[pi].edge_count >= uf[pi].size) {
                special_blocks++;
            }
        }
    }
 
    printf("%d\n", special_blocks);
    free(seen);
    return 0;
}