#include "stdio.h"
#include "stdlib.h"

#define MAX_VAL 10000

int main()
{
    int N;
    int K;
    scanf("%d %d", &N, &K);
    int *arr = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }

    int freq[MAX_VAL+1] = {0};
    int distinct_count = 0;

    for (int i = 0; i < K; ++i) {
        if (freq[arr[i]] == 0) {
            distinct_count++;  
        }
        freq[arr[i]]++;
    }

    if(N!=K)printf("%d", distinct_count);
    else printf("%d ", distinct_count);

    // Slide the window from index 1 to N-K
    for (int i = K; i < N; ++i) {
        // Remove the element going out of the window
        int element_out = arr[i - K];
        freq[element_out]--;
        if (freq[element_out] == 0) {
            distinct_count--;  
        }

        // Add the new element coming into the window
        int element_in = arr[i];
        if (freq[element_in] == 0) {
            distinct_count++;  
        }
        freq[element_in]++;

        printf(" %d", distinct_count);
    }

    free(arr);
    
}