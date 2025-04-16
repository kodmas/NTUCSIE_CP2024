#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int main(){
    int N,M;
    scanf("%d %d",&N,&M);

    int *arr = (int*)malloc(sizeof(int)*N);

    for(int i=0;i<N;i++){
        scanf("%d",&arr[i]);
    }

    int ans = 0;

    int i = 0;
    int j = N-1;

    while(i<j){
        if(pow((arr[i]+arr[j]),3) > M){
            j--;
        }else{
            ans += j-i;
            i++;
        }
    }

    printf("%d",ans);

    free(arr);
}