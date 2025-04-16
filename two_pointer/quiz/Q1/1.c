#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int main(){
    int N,M;
    scanf("%d",&N);
    scanf("%d",&M);

    int *arr = (int*)malloc(sizeof(int)*N);

    for(int i=0;i<N;i++){
        scanf("%d",&arr[i]);
    }

    int ans = pow(arr[0]+arr[1]+arr[2],3);

    int curr = 0;
    int i = 1;
    int j = N-1;

    for(curr=0;curr<N-2;curr++){
        i = curr+1;
        j = N-1;
        while(i<j){
            int sum = arr[curr]+arr[i]+arr[j];
            if(fabs(pow(sum,3)-M) < abs(ans-M)){
                ans = pow(sum,3);
            }
            if(sum < M){
                i++;
            }else{
                j--;
            }
        }
    }

    printf("%d",ans);

    free(arr);
}