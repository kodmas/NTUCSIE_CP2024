#include "stdio.h"  
#include "stdlib.h"

int main(){
    int N,k;
    scanf("%d %d",&N,&k);
    int *arr = (int*)malloc(N*sizeof(int));
    for(int i=0;i<N;i++){
        scanf("%d",&arr[i]);
    }

    int deque[N];

    int front = 0;
    int rear = 0;

    for(int i=0;i<k;i++){
        while(front!=rear && arr[i]>=arr[deque[rear-1]]){
            rear--;
        }
        deque[rear++] = i;
    }

    for(int i=k;i<N;i++){
        printf("%d ",arr[deque[front]]);
        while(front!=rear && deque[front]<=i-k){
            front++;
        }
        while(front!=rear && arr[i]>=arr[deque[rear-1]]){
            rear--;
        }
        deque[rear++] = i;
    }

    printf("%d ",arr[deque[front]]);
    return 0;
}