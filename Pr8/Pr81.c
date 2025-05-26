#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main() {
    int fd;
    char *buffer;
    size_t nbytes = 100000;
    ssize_t count;
    fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    buffer = malloc(nbytes);
    if (buffer == NULL) {
        perror("malloc");
        close(fd);
        exit(EXIT_FAILURE);
    }
    memset(buffer, 'A', nbytes);
    count = write(fd, buffer, nbytes);
    if (count == -1) {
        perror("write");
        free(buffer);
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Requested to write: %zu bytes\n", nbytes);
    printf("Actually written: %zd bytes\n", count);

    free(buffer);
    close(fd);
    return 0;
}