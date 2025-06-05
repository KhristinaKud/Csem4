#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#define MAX_LINE 1024
int main() {
    uid_t current_uid = getuid();
    struct passwd *current_user = getpwuid(current_uid);
    if (!current_user) {
        fprintf(stderr, "Error\n");
        return 1;
    }
    FILE *fp = popen("getent passwd", "r");
    if (!fp) {
        fprintf(stderr, "Error\n");
        return 1;
    }
    char line[MAX_LINE];
    printf("Regular users (UID > 1000), except for the current one (%s, UID: %d):\n", current_user->pw_name, current_uid);
    while (fgets(line, sizeof(line), fp)) {
        char *username = strtok(line, ":");
        strtok(NULL, ":");
        char *uid_str = strtok(NULL, ":");
        if (!username || !uid_str) {
            continue;
        }
        uid_t uid = atoi(uid_str);

        if (uid > 1000 && uid != current_uid) {
            printf("%s (UID: %d)\n", username, uid);
        }
    }


    int status = pclose(fp);
    if (status == -1) {
        fprintf(stderr, "Error\n");
        return 1;
    }


    return 0;
}