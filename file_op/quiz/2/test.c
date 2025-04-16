#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long getFileSize(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);

    return size;
}

void printLineSizes(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    char line[1024];
    int lineNumber = 1;
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("Size of line %d: %ld bytes\n", lineNumber, ftell(file) - ftell(file) + strlen(line));
        lineNumber++;
    }

    fclose(file);
}

int main() {
    const char *filename = "block_0_1.txt";
    long size = getFileSize(filename);

    if (size != -1) {
        printf("The size of the file '%s' is %ld bytes.\n", filename, size);
        printLineSizes(filename);
    }

    return 0;
}