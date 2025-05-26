#include <stdio.h>
#include <stdlib.h>

#define LINES 20

void view_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("fopen failed");
        return;
    }
    char line[1024];
    int line_count = 0;
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        if (++line_count == LINES) {
            printf("-- Press Enter to continue --");
            getchar();
            line_count = 0;
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> [file2]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        printf("File: %s\n", argv[i]);
        view_file(argv[i]);
    }

    return 0;
}
