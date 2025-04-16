#include <stdio.h>
#include <stdlib.h>


long long max(long long a, long long b) {
    return a > b ? a : b;
}

long long maxXORSum(int A[], int N) {
    long long sum = 0;
    int maxBit[30] = {0};  // Assuming 30-bit integers

    // Calculate initial sum and set up maxBit array
    for (int i = 0; i < N; i++) {
        sum += A[i];
        for (int j = 0; j < 30; j++) {
            if (A[i] & (1 << j)) {
                maxBit[j]++;
            }
        }
    }

    long long maxSum = sum;

    // Try flipping each bit
    for (int j = 29; j >= 0; j--) {
        int zeros = N - maxBit[j];
        if (zeros > maxBit[j]) {
            maxSum += (1LL << j) * (zeros - maxBit[j]);
        }
    }

    return maxSum;
}

int main() {
    int N;
    scanf("%d", &N);

    int A[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    long long result = maxXORSum(A, N);
    printf("%lld\n", result);

    return 0;
}