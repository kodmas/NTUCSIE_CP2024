#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    int N,k;

    scanf("%d",&N);
    scanf("%d",&k);
    long *arr = (long*)malloc(N*sizeof(long));
    for(int i=0;i<N;i++){
        scanf("%ld",&arr[i]);
    }

    if(k==0){
        for(int i=0;i<N;i++){
            if(i<N-1) printf("%ld ",arr[i]);
            else printf("%ld",arr[i]);
        }
        return 0;
    }
    else if(k == 32){
        for(int i=0;i<N;i++){
            if(i<N-1) printf("%ld ",0);
            else printf("%ld",0);
        }
        return 0;
    }
    
    long mask1 = 0;
    long mask2 = 0;

    int i = 0;
    while(i<32){
        for(int j=i;j<i+k;j++){
            mask1 = mask1 | (1<<j);
        }
        i+=2*k;
    }
    // printf("mask1\n");
    // for(int i=31;i>=0;i--){
    //     if(mask1 & 1<<i) printf("1");
    //     else printf("0");
    // }
    // printf("\n");
    i = k;
    // printf("i: %d\n",i);
    // printf("mask2\n");
    // for(int i=31;i>=0;i--){
    //     if(mask2 & 1<<i) printf("1");
    //     else printf("0");
    // }
    // printf("\n");
    while(i<32){
        for(int j=i;j<i+k;j++){
            // printf("j: %d\n",j);
            mask2 = mask2 | (1<<j);
        }
        i+=2*k;
    }
    for(int i=0;i<k;i++){
        mask2 = mask2 & ~(1<<i);
    }
    // printf("mask2\n");
    // for(int i=35;i>=0;i--){
    //     if(mask2 & 1<<i) printf("1");
    //     else printf("0");
    // }
    // printf("\n");

    // printf("\n");
    // for(int i=35;i>=0;i--){
    //     if(arr[0] & 1<<i) printf("1");
    //     else printf("0");
    // }
    // printf("\n");
    for(int i=0;i<N;i++){
        long temp = arr[i];
        // printf("temp: %ld\n",temp);
        int len = floor(log2(temp))+1;
        // printf("len: %d\n",len);
        long temp1 = (temp & mask1) << k;
        // printf("temp1\n");
        // for(int i=31;i>=0;i--){
        //     if(temp1 & 1<<i) printf("1");
        //     else printf("0");
        // }
        // printf("\n");
        long temp2 = (temp & mask2) >> k;
        // printf("temp2\n");
        // for(int i=31;i>=0;i--){
        //     if(temp2 & 1<<i) printf("1");
        //     else printf("0");
        // }
        // printf("\n");
        arr[i] = temp1 | temp2;

        // clear the bits that are not needed(including 1)
        for (int j = 32; j < (ceil(32.0/k) * k); j++) {
            arr[i] &= ~(1UL << j);
        }
    }

    for(int i=0;i<N;i++){
        if(i<N-1) printf("%ld ",arr[i]);
        else printf("%ld",arr[i]);
    }

    // printf("\n");
    // for(int i=35;i>=0;i--){
    //     if(arr[0] & 1<<i) printf("1");
    //     else printf("0");
    // }
    // printf("\n");
}