#include "stdio.h"
#include "stdlib.h"

int string_match(int index, int d, int r, int c,int l, int n, int* target, int** board){
    if(d < 0 || r < 0 || c < 0 || r >= n || c >= n){
        return 0;
    }
    if(index == l){
        return 1;
    }
    if(board[r][c] != target[index]){
        d--;
    }

    return string_match(index+1, d, r+1, c, l, n, target, board) || 
           string_match(index+1, d, r, c+1, l, n, target, board) || 
           string_match(index+1, d, r-1, c, l, n, target, board) || 
           string_match(index+1, d, r, c-1, l, n, target, board);
}


int main(){
    int n,l,d;
    scanf("%d %d %d\n", &n, &l, &d);

    int* target = (int*)malloc(l*sizeof(int));
    char* temp = (char*)malloc(l*sizeof(char));

    for(int i=0; i<l; i++){
        scanf("%c", &temp[i]);
        target[i] = temp[i] - '0';
    }


    int** board = (int**)malloc(n*sizeof(int*));
    for(int i=0; i<n; i++){
        board[i] = (int*)malloc(n*sizeof(int));
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%d", &board[i][j]);
        }
        scanf("\n");
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(string_match(0, d, i, j, l, n, target, board)){
                printf("true");
                return 0;
            }
        }
    }

    printf("false");
    return 0;


}