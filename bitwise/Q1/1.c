#include <stdio.h>
#include <stdlib.h>

int main(){
    int Q;
    scanf("%d", &Q);

    for(int i = 0; i < Q; i++){
        int N;
        scanf("%d", &N);

        long *arr = (long *)malloc(N * sizeof(long));
        for(int j = 0; j < N; j++){
            scanf("%ld", &arr[j]);
        }

        for(int j = 0; j < N; j++){
            // bitwise swap odd bits with even bits
            arr[j] = ((arr[j] & 0xAAAAAAAA) >> 1) | ((arr[j] & 0x55555555) << 1);
            
            if(j < N-1) printf("%ld ", arr[j]);
            else printf("%ld", arr[j]);
        }
        printf("\n");

        free(arr);
    }
}