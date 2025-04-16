#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024
#define COMMAND_SIZE 128

int main() {
    char filename[128];
    char buffer[BUFFER_SIZE] = {0};
    FILE *f = NULL;

    scanf("%s", filename);
    if (strcmp(filename, "exit") == 0) return 0;

    f = fopen(filename, "w+");
    // if (!f) {
    //     perror("Failed to open file");
    //     return 1;
    // }

    while (true) {
        char command[COMMAND_SIZE];
        scanf("%s", command);

        if (strcmp(command, "exit") == 0) {
            fclose(f);
            break;
        } else if (strcmp(command, "close") == 0) {
            fclose(f);
            memset(buffer, 0, sizeof(buffer));
            memset(filename, 0, sizeof(filename));
            scanf("%s", filename);
            if (strcmp(filename, "exit") == 0) break;
            else{
                f = fopen(filename, "a+");
            }
            // f = fopen(filename, "w+");
            // if (!f) {
            //     perror("Failed to open file");
            //     return 1;
            // }
        } else if (strcmp(command, "add") == 0) {
            int n;
            scanf("%d", &n);
            getchar(); // Consume the trailing newline character.

            for (int i = 0; i < n; i++) {
                char line[COMMAND_SIZE];
                if (fgets(line, sizeof(line), stdin) != NULL) {
                    line[strcspn(line, "\n")] = '\0'; // Remove trailing newline.
                    if (strlen(buffer) + strlen(line) + 1 < BUFFER_SIZE) {
                        strcat(buffer, line);
                        strcat(buffer, "\n");
                    } else {
                        fprintf(stderr, "Buffer overflow, line skipped.\n");
                    }
                }
            }
        } else if (strcmp(command, "clear") == 0) {
            memset(buffer, 0, sizeof(buffer));
        } else if (strcmp(command, "status") == 0) {
            printf("%s", buffer);
        } else if (strcmp(command, "push") == 0) {
            if (f) {
                fseek(f, 0, SEEK_END);
                fprintf(f, "%s", buffer);
                fflush(f);
                memset(buffer, 0, sizeof(buffer));
            }
        } else if (strcmp(command, "pull") == 0) {
            fseek(f, 0, SEEK_SET);
            char fileBuffer[BUFFER_SIZE];
            while (fgets(fileBuffer, sizeof(fileBuffer), f) != NULL) {
                printf("%s", fileBuffer);
            }
        } else if (strcmp(command, "truncate") == 0) {
            fclose(f);
            f = fopen(filename, "w+");
            // if (!f) {
            //     perror("Failed to truncate file");
            //     return 1;
            // }
            printf("File truncated.\n");
        } else {
            printf("Invalid command.\n");
        }
    }

    return 0;
}
