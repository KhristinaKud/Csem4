#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd = open("test.txt", O_WRONLY | O_CREAT, 0644);
    char buffer[] = "Hello";
    ssize_t count = write(fd, buffer, 5);
    printf("Written %zd bytes out of 5\n", count);
    close(fd);
    return 0;
}