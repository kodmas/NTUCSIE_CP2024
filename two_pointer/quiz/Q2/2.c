#include "stdio.h"
#include "stdlib.h"

int main(){
    int N,M,K;
    scanf("%d %d %d",&N,&M,&K);
    
    int *a = (int *)malloc(N*sizeof(int));
    int *b = (int *)malloc(M*sizeof(int));

    for(int i=0;i<N;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<M;i++){
        scanf("%d",&b[i]);
    }

    int i=0,j=0;
    int ans = 0;
    int j_skip = 0;

    while(i<N && j<M){
        if(abs(a[i]-b[j]) == K){
            ans++;
            if(a[i] > b[j]){
                j++;
            }
            else{
                i++;
                j = j_skip;
            }
        }
        else if(abs(a[i]-b[j]) < K){
            if(j!=M-1)j++;
            else {
                i++;
                j = j_skip;
            }
        }
        else{
            if(a[i] > b[j]){
                j++;
                j_skip = j;
            }
            else{
                i++;
                j = j_skip;
            }
        }
    }


    printf("%d",ans);


    free(a);
    free(b);
}