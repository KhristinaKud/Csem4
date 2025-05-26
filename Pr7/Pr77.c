#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir failed");
        return 1;
    }

    struct dirent *entry;
    char response;

    while ((entry = readdir(dir))) {
        if (strstr(entry->d_name, ".c") == NULL) continue;

        printf("File: %s\n", entry->d_name);
        printf("Grant read permission to others? (y/n): ");
        scanf(" %c", &response);

        if (response == 'y' || response == 'Y') {
            struct stat st;
            if (stat(entry->d_name, &st) == -1) {
                perror("stat failed");
                continue;
            }
            if (chmod(entry->d_name, st.st_mode | S_IROTH) == -1) {
                perror("chmod failed");
            }
            else {
              printf("Permissions updated\n");
              }
        }
    }

    closedir(dir);
    return 0;
}
