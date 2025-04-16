#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_LINE_LENGTH 100
#define MAX_FILES 100

// Function to calculate XOR mod 2^30 with special handling for multiples of 25
uint32_t modify_data(const char *filename, int line_num, int new_data) {
    printf("in %s\n", filename);
    FILE *file = fopen(filename, "r+");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    uint32_t result = 0;
    int i=0;
    int data_start_pos = 0;
    int data_start_flag = 0;
    int data_line_len = 0;
    int mystery = 0;    // Mystery variable
    // Process each line in the file
    while (fgets(line, sizeof(line), file)) {
        printf("line %s\n", line);
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
                data_start_pos = ftell(file);
                data_start_flag = 1;
                continue;  // Skip the P line
            } else if (strcmp(key, "N") == 0) {
                result ^= value; // Include N in XOR
                result %= (1 << 30);
            }
        }
        else{
            i++;
            printf("i = %d\n", i);
            char *cur_data = line;
            int value = atoi(cur_data);
            if(data_start_flag == 0){
                data_line_len = strlen(line);
            }
            if(i == line_num){
                value = new_data;
                mystery = ftell(file);
                printf("mystery = %d\n", mystery);
            }

            if(i % 25 == 0){
                result ^= value;
                result = (result << 1) % (1 << 30);
            }
            else{
                result ^= value;
                result %= (1 << 30);
            }
        }
    }

    fclose(file);

    // Open the file again to write the new data
    file = fopen(filename, "r+");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    fseek(file, mystery, SEEK_SET);
    fprintf(file, "%d\n", new_data);
    return result;
}

uint32_t modify_data(const char *filename, int line_num, int new_data) {
    printf("in %s\n", filename);
    FILE *file = fopen(filename, "r+");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    uint32_t result = 0;
    int i=0;
    int data_start_pos = 0;
    int data_start_flag = 0;
    int data_line_len = 0;
    int mystery = 0;    // Mystery variable
    // Process each line in the file
    while (fgets(line, sizeof(line), file)) {
        printf("line %s\n", line);
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
                data_start_pos = ftell(file);
                data_start_flag = 1;
                continue;  // Skip the P line
            } else if (strcmp(key, "N") == 0) {
                result ^= value; // Include N in XOR
                result %= (1 << 30);
            }
        }
        else{
            i++;
            printf("i = %d\n", i);
            char *cur_data = line;
            int value = atoi(cur_data);
            if(data_start_flag == 0){
                data_line_len = strlen(line);
            }
            if(i == line_num){
                value = new_data;
                mystery = ftell(file);
                printf("mystery = %d\n", mystery);
            }

            if(i % 25 == 0){
                result ^= value;
                result = (result << 1) % (1 << 30);
            }
            else{
                result ^= value;
                result %= (1 << 30);
            }
        }
    }

    fclose(file);

    // Open the file again to write the new data
    file = fopen(filename, "r+");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    fseek(file, mystery, SEEK_SET);
    fprintf(file, "%d\n", new_data);
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
    int q;
    int memory[1000][3];

    int ans = 0;
    // Read the input for the number of files and their names
    scanf("%d %d", &num_files, &q);

    for (int i = 1; i <= num_files; i++) {
        if (scanf("%s", filenames[i]) != 1) {
            fprintf(stderr, "Error: Invalid file name input.\n");
            return EXIT_FAILURE;
        }
        printf("%s\n", filenames[i]);
    }

    for(int i=0; i<q; i++){
        scanf("%d %d %d", &memory[i][0], &memory[i][1], &memory[i][2]);
    }

    for(int i=0;i<q;i++){
        printf("%d %d %d\n", memory[i][0], memory[i][1], memory[i][2]);
        const char *curr_file = filenames[memory[i][0]];
        const char *next_file = filenames[memory[i][0]+1];

        uint32_t expected_p = extract_p_value(next_file);
        
        uint32_t calculated_p = modify_data(curr_file, memory[i][1], memory[i][2]);

        if(expected_p != calculated_p){
            uint32_t new_nonce = calculated_p ^ expected_p;
            
            ans++;
            FILE *file = fopen(curr_file, "r");

        }

    }
    // Iterate through files and perform the validity check
    // for (int i = 1; i < num_files; ++i) {
    //     const char *prev_file = filenames[i - 1];
    //     const char *curr_file = filenames[i];

    //     uint32_t calculated_p = calculate_xor_mod(prev_file);
    //     uint32_t expected_p = extract_p_value(curr_file);

    //     if (calculated_p != expected_p) {
    //         printf("%d", i);
    //         return 0;
    //     }
    // }

    // If all files are valid
    printf("-1");
    return 0;
}
