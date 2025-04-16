#include "stdio.h"
#include "stdlib.h"

int main(){
    int N;
    scanf("%d", &N);
    int *A = (int *)malloc(N * sizeof(int));
    for(int i = 0; i < N; i++){
        scanf("%d", &A[i]);
    }
    int M;
    scanf("%d", &M);
    int *B = (int *)malloc(M * sizeof(int));
    for(int i = 0; i < M; i++){
        scanf("%d", &B[i]);
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(A[i+j] != B[j]){
                break;
            }
            if(j == M-1){
                printf("%d ", i);
            }
        }
    }

}