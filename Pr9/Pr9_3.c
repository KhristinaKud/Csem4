#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main() {
    pid_t pid;
    int fd;
    const char *filename = "/tmp/testfile";
    const char *user_home = "/home/user/testfile_copy";

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    write(fd, "Mama mia\n", strlen("Mama mia\n"));
    close(fd);

    printf("Copy file for root\n");
    if (chmod(filename, 0644) == -1) {
        perror("Помилка при зміні прав файлу");
    }
    if (rename(filename, user_home) == -1) {
        perror("Error copying file");
        exit(EXIT_FAILURE);
    }
    printf("Change file user \n");
    fd = open(user_home, O_WRONLY | O_APPEND);
    if (fd == -1) {
        perror("Error opening file");
    } else {
        if (write(fd, " Hello world\n", strlen(" Hello world\n")) == -1) {
            perror("Error writing to file");
        } else {
            printf("File successfully change\n");
        }
        close(fd);
    }


    printf("Remove file\n");
    if (remove(user_home)) {
        perror("Помилка при видаленні файлу");
    } else {
        printf("Файл успішно видалено\n");
    }

    return 0;
}