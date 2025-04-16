#include "stdio.h"
#include "stdlib.h"

int main(){
    int N,M;
    scanf("%d %d",&N,&M);
    
    int *a = (int *)malloc(N*sizeof(int));
    int *b = (int *)malloc(M*sizeof(int));

    for(int i=0;i<N;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<M;i++){
        scanf("%d",&b[i]);
    }

    int i=0,j=1;
    int min_dis = abs(a[0]-b[0]);
    
    while(i<N && j<M){
        if(abs(a[i]-b[j]) <= min_dis){
            min_dis = abs(a[i]-b[j]);
            j++;
        }
        else{
            if(i!=N-1) printf("%d ",min_dis);
            else printf("%d\n",min_dis);
            i++;
            min_dis = abs(a[i]-b[j-1]);
        }  
    }

    while(i<N){
        min_dis = abs(a[i]-b[M-1]);
        if(i!=N-1) printf("%d ",min_dis);
        else printf("%d\n",min_dis);
        i++;
    }

    free(a);
    free(b);
}