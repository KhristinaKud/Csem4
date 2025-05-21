#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Us: %s <file> <word>\n", argv[0]);
        return 1;
    }
    const char *filename = argv[1];
    const char *word = argv[2];
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, file)) {
        if (strstr(buffer, word)) {
            printf("%s", buffer);
        }
    }
    fclose(file);
    return 0;
}
