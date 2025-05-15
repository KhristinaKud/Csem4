#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("data.bin", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    write(fd, data, 10);
    lseek(fd, 3, SEEK_SET);

    unsigned char buffer[4];
    ssize_t count = read(fd, buffer, 4);

    printf("Read %ld bytes: ", count);
    for (int i = 0; i < count; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
    close(fd);
    return 0;
}