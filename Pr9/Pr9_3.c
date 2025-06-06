#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#define ORIGINAL_FILE "original.txt"
#define COPY_FILE "copy.txt"

int main() {
    printf("Creating a file as a regular user...\n");
    int fd = open(ORIGINAL_FILE, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Error creating file");
        return 1;
    }
    const char *content = "This is the original file.\n";
    write(fd, content, strlen(content));
    close(fd);
    printf("File %s created.\n", ORIGINAL_FILE);
    if (geteuid() != 0) {
        fprintf(stderr, "This program must be run as root (sudo).\n");
        return 1;
    }

    char *home_dir = getenv("HOME");
    if (!home_dir) {
        fprintf(stderr, "Failed to get home directory.\n");
        return 1;
    }
    char copy_path[256];
    snprintf(copy_path, sizeof(copy_path), "%s/%s", home_dir, COPY_FILE);

    printf("Copying file as root to %s...\n", copy_path);
    FILE *src = fopen(ORIGINAL_FILE, "r");
    if (!src) {
        perror("Error opening original file");
        return 1;
    }
    FILE *dst = fopen(copy_path, "w");
    if (!dst) {
        perror("Error creating copy file");
        fclose(src);
        return 1;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dst);
    }
    fclose(src);
    fclose(dst);
    printf("File copied to %s.\n", copy_path);

    printf("Changing ownership of file %s to root...\n", copy_path);
    if (chown(copy_path, 0, 0) == -1) {
        perror("Error changing file ownership");
        return 1;
    }

    printf("Attempting to modify file as a regular user...\n");
    if (seteuid(getuid()) == -1) {
        perror("Error changing effective UID to regular user");
        return 1;
    }

    int fd_copy = open(copy_path, O_WRONLY | O_APPEND);
    if (fd_copy == -1) {
        perror("Error: could not open file for writing as a regular user");
    } else {
        const char *new_content = "Adding new text.\n";
        write(fd_copy, new_content, strlen(new_content));
        close(fd_copy);
        printf("File successfully modified.\n");
    }

    printf("Attempting to delete file as a regular user...\n");
    if (unlink(copy_path) == -1) {
        perror("Error: could not delete file as a regular user");
    } else {
        printf("File %s successfully deleted.\n", copy_path);
    }

    return 0;
}
