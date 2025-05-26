#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_files(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char full_path[1024];

    if (!(dir = opendir(path))) {
        perror(path);
        return;
    }

    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &st) == -1) {
            perror(full_path);
            continue;
        }
        if (S_ISDIR(st.st_mode)) {
            list_files(full_path);
        } else{
          printf("%s\n", full_path);
        }
    }

    closedir(dir);
}

int main() {
    printf("Directory:\n");
    list_files(".");
    return 0;
}
