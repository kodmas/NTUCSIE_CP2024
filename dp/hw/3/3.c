#include <stdio.h>
#include <stdlib.h>


int main(){
    int N;
    scanf("%d", &N);

    int *arr = (int *)malloc(N * sizeof(int));
    for(int i = 0; i < N; i++){
        scanf("%d", &arr[i]);
    }

    long long *dp = (long long *)malloc(N * sizeof(long long));

    dp[0] = (arr[0] != 0) ? 1 : 0;

    for(int i=0;i<N;i++){
        int j = i+1;
        while(j<=i+arr[i] && j<N){
            if(arr[j] == 0 && j != N-1){
                j++;
                continue;
            }
            dp[j] += dp[i];
            j++;
        }
    }

    for(int i=0;i<N;i++){
        printf("%lld ", dp[i]);
    }
    printf("\n");
    printf("%lld", dp[N-1]);

    return 0;
}