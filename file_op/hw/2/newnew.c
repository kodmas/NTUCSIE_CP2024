#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_LINE_LENGTH 100
#define MAX_FILES 100

// Function to calculate XOR mod 2^30 with special handling for multiples of 25
uint32_t calculate_xor_mod(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    uint32_t result = 0;
    int i=0;
    // Process each line in the file
    while (fgets(line, sizeof(line), file)) {
        // Locate the ':' character in the line
        char *colon_pos = strchr(line, ':');
        if (colon_pos) {
            // Parse the key and value
            *colon_pos = '\0';  // Split the line at ':'
            char *key = line;   // Key is the part before ':'
            char *value_str = colon_pos + 1; // Value is the part after ':'

            // Trim whitespace around key and value
            int key_value = atoi(key);  // Convert key to integer if numeric
            int value = atoi(value_str); // Convert value to integer

            if (strcmp(key, "P") == 0) {
                continue;  // Skip the P line
            } else if (strcmp(key, "N") == 0) {
                result ^= value; // Include N in XOR
                if(i%25 == 24) result = (result << 1) % (1 << 30);
                else result %= (1 << 30);
            } else {
                i = key_value;
                // Handle numeric keys
                if (key_value % 25 == 0) {
                    result ^= value;
                    result = (result << 1) % (1 << 30);
                } else {
                    result ^= value;
                    result %= (1 << 30);
                }
            }
        }
    }

    fclose(file);
    return result;
}


// Function to extract the "P" value from a file
uint32_t extract_p_value(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    uint32_t p_value = 0;

    // Read the "P" value from the file
    while (fgets(line, sizeof(line), file)) {
        char key;
        int value;
        if (sscanf(line, "%c: %d", &key, &value) == 2 && key == 'P') {
            p_value = value;
            break;
        }
    }

    fclose(file);
    return p_value;
}

int main() {
    char filenames[MAX_FILES][MAX_LINE_LENGTH];
    int num_files;

    // Read the input for the number of files and their names
    if (scanf("%d", &num_files) != 1 || num_files < 2) {
        fprintf(stderr, "Error: Invalid input. The number of files must be at least 2.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < num_files; i++) {
        if (scanf("%s", filenames[i]) != 1) {
            fprintf(stderr, "Error: Invalid file name input.\n");
            return EXIT_FAILURE;
        }
    }

    // Iterate through files and perform the validity check
    for (int i = 1; i < num_files; ++i) {
        const char *prev_file = filenames[i - 1];
        const char *curr_file = filenames[i];

        uint32_t calculated_p = calculate_xor_mod(prev_file);
        uint32_t expected_p = extract_p_value(curr_file);

        if (calculated_p != expected_p) {
            printf("%d", i);
            return 0;
        }
    }

    // If all files are valid
    printf("-1");
    return 0;
}
