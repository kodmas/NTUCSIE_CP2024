#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void KMPSearch(char* pat, char* txt) {
    int M = strlen(pat);
    int N = strlen(txt);

    int* lps = (int*)malloc(M * sizeof(int));
    computeLPSArray(pat, M, lps);

    int i = 0, j = 0;
    int found = 0; // Flag to track if a match is found
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j == M) {
            printf("%d\n", i - j);
            found = 1; // Mark that a match is found
            j = lps[j - 1];
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    if (!found) { // If no occurrences were found
        printf("-1\n");
    }
    free(lps);
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

    KMPSearch(txt, pat);

    fclose(file);
    free(pat);
    free(txt);
    return 0;
}
