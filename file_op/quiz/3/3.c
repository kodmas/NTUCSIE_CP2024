#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to compute the LPS (Longest Prefix Suffix) array
void computeLPSArray(char* pat, int M, int* lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Function to perform KMP search for a pattern in a text
int KMPSearch(char* pat, char* txt) {
    int M = strlen(pat);
    int N = strlen(txt);

    int* lps = (int*)malloc(M * sizeof(int));
    computeLPSArray(pat, M, lps);

    int i = 0, j = 0;
    int found = 0;

    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j == M) {
            printf("%d\n", i - j);
            found = 1;
            j = lps[j - 1];
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    free(lps);
    return found;
}

// Function to process suffixes of the pattern
void findSuffixOccurrences(char* txt, char* pat) {
    int len = strlen(pat);

    // Iterate through all suffixes of the pattern
    for (int i = len - 1; i >= 0; i--) {
        // printf("Suffix: %s\n", pat + i); // Optional: Print the current suffix being searched
        int found = KMPSearch(pat + i, txt);
        if (!found) {
            printf("-1\n");
        }
    }
}

int main() {
    char filename[100];
    scanf("%s", filename);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char* pat = (char*)malloc(1000000 * sizeof(char));
    char* txt = (char*)malloc(1000000 * sizeof(char));
    if (fscanf(file, "%s", pat) != 1 || fscanf(file, "%s", txt) != 1) {
        fprintf(stderr, "Error: Failed to read strings from file.\n");
        fclose(file);
        free(pat);
        free(txt);
        return 1;
    }

    findSuffixOccurrences(pat, txt);

    fclose(file);
    free(pat);
    free(txt);
    return 0;
}
