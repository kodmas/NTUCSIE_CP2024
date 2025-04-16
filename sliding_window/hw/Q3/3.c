#include "stdio.h"
#include "stdlib.h"

int main(){
    int N,L;

    scanf("%d %d", &N, &L);

    long *arr = (long*)malloc(N * sizeof(long));

    for(int i=0;i<N;i++){
        scanf("%ld", &arr[i]);
    }

    long long sum = 0;
    long long max_sum = 0;
    int left = 0;

    for(int i=0;i<L;i++){
        sum += arr[i];
    }

    max_sum = sum;

    for(int i=L;i<N;i++){
        sum += arr[i] - arr[i-L];
        if(sum >= max_sum){
            max_sum = sum;
            left = i - L + 1;
        }
    }

    printf("%lld %d",max_sum, left+1);
}