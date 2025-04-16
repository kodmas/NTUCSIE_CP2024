#include <stdio.h>
#include <stdlib.h>


int main(){
    int N;
    scanf("%d", &N);

    int *arr = (int *)malloc(N * sizeof(int));
    for(int i = 0; i < N; i++){
        scanf("%d", &arr[i]);
    }

    int *cost = (int *)malloc(N * sizeof(int));

    for(int i = 0; i < N; i++){
        scanf("%d", &cost[i]);
    }

    int budget;
    scanf("%d", &budget);

    int*** dp = (int ***)malloc(N * sizeof(int **));
    for(int i = 0; i < N; i++){
        dp[i] = (int **)malloc(N * sizeof(int *));
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            dp[i][j] = (int *)malloc(2 * sizeof(int));
        }
    }

    for(int i=0;i<N;i++){
        if(arr[0] == 0){
            dp[0][i][0] = 0;
            dp[0][i][1] = 0;
        }
        else{
            dp[0][i][0] = 1;
            dp[0][i][1] = cost[0];
        }
    }


    for(int i=0;i<N;i++){
        int j = i+1;
        while(j<=i+arr[i] && j<N){
            if(arr[j] == 0 && j != N-1){
                j++;
                continue;
            }
            if(dp[j][i][0]) continue;
        }
    }

    for(int i=0;i<N;i++){
        printf("%lld ", dp[i]);
    }
    printf("\n");
    printf("%lld", dp[N-1]);

    return 0;
}