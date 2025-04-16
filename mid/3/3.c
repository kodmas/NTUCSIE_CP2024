#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Helper function to check if str1 (possibly modified) is a subsequence of str2
bool isSubsequenceWithShift(char *A, char *B, int k) {
    int lenA = strlen(A);
    int lenB = strlen(B);
    int j = 0;  // Pointer for A

    // Traverse B and try to match characters from A
    for (int i = 0; i < lenB && j < lenA; i++) {
        // Check if current character of A matches current character of B
        if (A[j] == B[i]) {
            j++;  // Match without shifting
        }
        // Check if the shifted version of A[j] matches B[i]
        else if (((A[j] - 'a' - k + 26) % 26) + 'a' == B[i]) {
            j++;  // Match after shifting
        }
    }

    // If we've matched all characters of A, return true
    return (j == lenA);
}

int canTransformToSubsequence(char *A, char *B) {
    // Try all possible shifts k from 0 to 25
    for (int k = 0; k < 26; k++) {
        if (isSubsequenceWithShift(A, B, k)) {
            return k;
        }
    }
    return -1;
}

int main() {
    
    char A[1000], B[1000];
    scanf("%s %s", A, B);

    int result = canTransformToSubsequence(A, B);

    printf("%d", result);


    return 0;
}
