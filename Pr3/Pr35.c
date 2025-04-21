#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1024

void copy_file(const char *src, const char *dst) {
    FILE *task35 = fopen(src, "rb");
    if (task35 == NULL) {
        printf("Cannot open file %s for reading\n", src);
        exit(1);
    }

    FILE *copytask35 = fopen(dst, "wb");
    if (copytask35 == NULL) {
        fclose(task35);
        printf("Cannot open file %s for writing\n", dst);
        exit(1);
    }

    char buffer[MAX_SIZE];
    size_t bytes_read, bytes_written;
    long file_size = 0;

    while ((bytes_read = fread(buffer, 1, MAX_SIZE, task35)) > 0) {
        file_size += bytes_read;
        if (file_size > MAX_SIZE) {
            printf("File size is over the limit\n");
            fclose(task35);
            fclose(copytask35);
            return;
        }

        bytes_written = fwrite(buffer, 1, bytes_read, copytask35);
        if (bytes_written != bytes_read) {
            printf("Error writing to file %s\n", dst);
            fclose(task35);
            fclose(copytask35);
            return;
        }
    }

    fclose(task35);
    fclose(copytask35);
    printf("File copied successfully.\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Program need two arguments\n");
        return 1;
    }

    copy_file(argv[1], argv[2]);
    return 0;
}
