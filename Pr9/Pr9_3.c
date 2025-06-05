#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <pwd.h>

int main() {
    pid_t pid;
    int fd;
    const char *filename = "/tmp/testfile";
    const char *user_home = "/home/user/testfile_copy";
    struct passwd *pwd;

    // Створення файлу від імені звичайного користувача
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Помилка при відкритті файлу");
        exit(EXIT_FAILURE);
    }
    write(fd, "Mama mia\n", strlen("Mama mia\n"));
    close(fd);

    printf("Копіювання файлу у домашній каталог користувача\n");
    if (chmod(filename, 0644) == -1) {
        perror("Помилка при зміні прав файлу");
    }
    if (rename(filename, user_home) == -1) {
        perror("Помилка при копіюванні файлу");
        exit(EXIT_FAILURE);
    }

    // Отримання інформації про звичайного користувача
    pwd = getpwnam("user"); // Змініть "user" на вашого фактичного користувача
    if (!pwd) {
        perror("Помилка при отриманні UID користувача");
        exit(EXIT_FAILURE);
    }

    // Зміна власника файлу на звичайного користувача
    printf("Зміна власника файлу\n");
    if (chown(user_home, pwd->pw_uid, pwd->pw_gid) == -1) {
        perror("Помилка при зміні власника файлу");
        exit(EXIT_FAILURE);
    }

    // Зміна файлу звичайним користувачем
    printf("Зміна файлу користувачем\n");
    fd = open(user_home, O_WRONLY | O_APPEND);
    if (fd == -1) {
        perror("Помилка при відкритті файлу");
    } else {
        if (write(fd, "Hello world\n", strlen("Hello world\n")) == -1) {
            perror("Помилка при записі у файл");
        } else {
            printf("Файл успішно змінено\n");
        }
        close(fd);
    }

    // Видалення файлу
    printf("Видалення файлу\n");
    if (remove(user_home)) {
        perror("Помилка при видаленні файлу");
    } else {
        printf("Файл успішно видалено\n");
    }

    return 0;
}
