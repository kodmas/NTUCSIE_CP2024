#include <stdio.h>
#include <stdlib.h>

int main(){
    int N;
    scanf("%d", &N);

    int *arr = (int *)malloc(N * sizeof(int));

    for(int i = 0; i < N; i++){
        scanf("%d", &arr[i]);
    }

    int ans = 0;
    // check each bit of the number
    for(int i=0;i<32;i++){
        int count = 0;
        for(int j=0;j<N;j++){
            if(arr[j] & (1 << i)) count++;
        }
        
        if(count > N/2) ans |= (1 << i);
    }

    printf("%d\n", ans);

    long total = 0;

    for(int i = 0; i < N; i++){
        total += arr[i] ^ ans;
    }

    printf("%ld", total);
    
    free(arr);
}