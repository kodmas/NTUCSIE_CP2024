#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024
#define COMMAND_SIZE 128

int main() {
    int version_mem[1024];
    for(int i = 0; i < 1024; i++){
        version_mem[i] = 1;
    }
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
    int version = 1;
    char* dummy = "---\n";
    while (true) {
        char command[COMMAND_SIZE];
        scanf("%s", command);

        if (strcmp(command, "exit") == 0) {
            fclose(f);
            break;
        } else if (strcmp(command, "close") == 0) {
            fclose(f);
            version_mem[filename[5] - '0'] = version;
            memset(buffer, 0, sizeof(buffer));
            memset(filename, 0, sizeof(filename));
            scanf("%s", filename);
            char file_num = filename[5];
            int num = file_num - '0';
            version = version_mem[num];
            if (strcmp(filename, "exit") == 0) break;
            else{
                f = fopen(filename, "a+");
            }
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
                char versionBuffer[128];
                sprintf(versionBuffer, "Version %d\n", version++);
                fprintf(f, "%s", versionBuffer);
                fprintf(f, "%s", buffer);
                fprintf(f, "%s", dummy);
                fflush(f);
                memset(buffer, 0, sizeof(buffer));
                printf("%s Version %d saved.\n", filename, version-1);
            }
        } else if (strcmp(command, "pull") == 0) {
            fseek(f, 0, SEEK_SET);
            char fileBuffer[BUFFER_SIZE];
            int tmp = 0;
            while (fgets(fileBuffer, sizeof(fileBuffer), f) != NULL) {
                if(tmp == 0){
                    tmp++;
                    continue;
                }else if(strcmp(fileBuffer, "---\n") == 0){
                    tmp = 0;
                    continue;
                } else printf("%s", fileBuffer);
            }
        } else if (strcmp(command, "truncate") == 0) {
            fclose(f);
            f = fopen(filename, "w+");
            printf("File truncated.\n");
            version = 1;
        } else if(strcmp(command, "log") == 0){
            fseek(f, 0, SEEK_SET);
            char fileBuffer[BUFFER_SIZE];
            int tmp = 0;
            int cur_v = 1;
            int v = 1;
            while(v < version){
                fseek(f, 0, SEEK_SET);
                printf("Version %d\n", v);
                v++;
                while(cur_v < v+1){
                    // printf("test %d %d\n", cur_v, v);
                    fgets(fileBuffer, sizeof(fileBuffer), f);
                    if(tmp == 0){
                        tmp++;
                        cur_v++;
                        continue;
                    }else if(strcmp(fileBuffer, "---\n") == 0){
                        tmp = 0;
                        continue;
                    }else printf("%s", fileBuffer);
                }
                tmp = 0;
                cur_v = 1;
                printf("%s", "---\n");
            }
        } else if(strcmp(command, "version") == 0){
            int n;
            scanf("%d", &n);
            if(n >= version){
                printf("Invalid version.\n");
                continue;
            }
            getchar(); // Consume the trailing newline character.

            fseek(f, 0, SEEK_SET);
            char fileBuffer[BUFFER_SIZE];
            int tmp = 0;
            int cur_v = 1;
            while (fgets(fileBuffer, sizeof(fileBuffer), f) != NULL) {
                if(cur_v > n+1){
                    break;
                }
                if(tmp == 0){
                    tmp++;
                    cur_v++;
                    continue;
                }else if(strcmp(fileBuffer, "---\n") == 0){
                    // printf("\n");
                    tmp = 0;
                    continue;
                } else printf("%s", fileBuffer);
            }
        }
        else {
            printf("Invalid command.\n");
        }
    }

    return 0;
}
