#include <stdio.h>
#include <string.h>

// Function to return the complementary nucleotide
char complement(char base) {
    switch(base) {
        case 'A': return 'T';
        case 'T': return 'A';
        case 'C': return 'G';
        case 'G': return 'C';
        default: return '\0';  // Non-standard characters
    }
}

int main() {
    int N;
    char S[201];

    // Input the length of the DNA sequence and the sequence itself
    scanf("%d", &N);
    scanf("%s", S);

    // Find the position of the first non-standard character
    int non_standard_pos = -1;
    for (int i = 0; i < N; i++) {
        if (S[i] != 'A' && S[i] != 'T' && S[i] != 'C' && S[i] != 'G') {
            non_standard_pos = i;
            break;
        }
    }

    // If no non-standard character was found or it's at the end
    if (non_standard_pos == -1 || non_standard_pos == N - 1) {
        printf("-1\n");
        printf("Not a Super Smart Sheep\n");
        return 0;
    }

    // Variables to store the result
    int max_len = -1;
    int best_left_start = -1, best_right_start = -1;
    int best_half_len = 0;

    // Iterate over all possible starting positions for the left half
    for (int i = non_standard_pos + 1; i < N; i++) {
        // For each possible starting point of the left half, find the matching right half
        for (int j = i + 1; j < N; j++) {
            int l = i;
            int r = j;
            int half_len = 0;
            int is_palindrome = 1;

            // Expand while matching complementary pairs between the left and right halves
            while (l >= non_standard_pos + 1 && r < N) {
                if (complement(S[l]) != S[r]) {
                    is_palindrome = 0;
                    break;
                }
                l--;
                r++;
                half_len++;
            }

            // If a valid palindrome is found, update the maximum length
            if (is_palindrome) {
                int palindrome_len = half_len * 2;
                if (palindrome_len > max_len) {
                    max_len = palindrome_len;
                    best_left_start = i;
                    best_right_start = j;
                    best_half_len = half_len;
                }
            }
        }
    }

    // Output the result
    if (max_len == -1) {
        printf("-1\n");
        printf("Not a Super Smart Sheep\n");
    } else {
        printf("%d\n", max_len);

        // Print the first half of the palindrome
        for (int i = best_left_start - best_half_len + 1; i <= best_left_start; i++) {
            putchar(S[i]);
        }

        printf(" ");

        // Print the second half of the palindrome
        for (int i = best_right_start; i < best_right_start + best_half_len; i++) {
            putchar(S[i]);
        }

        printf("\n");
    }

    return 0;
}
