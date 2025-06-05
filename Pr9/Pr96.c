#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void check_access(const char *filename) {
    printf("\nChecking: %s\n", filename);

    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ls -l %s 2>/dev/null", filename);
    printf("Permissions:\n");
    system(cmd);

    printf("Access check:\n");
    printf("  Read:    %s\n", access(filename, R_OK) == 0 ? "YES" : "NO");
    printf("  Write:   %s\n", access(filename, W_OK) == 0 ? "YES" : "NO");
    printf("  Execute: %s\n", access(filename, X_OK) == 0 ? "YES" : "NO");

    FILE *f = fopen(filename, "r");
    if (f) {
        printf("  Can read content: YES\n");
        fclose(f);
    } else {
        printf("  Can read content: NO\n");
    }
}

int main() {
    printf(" Home directory\n");
    system("ls -l ~ ");

    printf("\n /usr/bin \n");
    system("ls -l /usr/bin | head -10");

    printf("\n/etc \n");
    system("ls -l /etc | head -10");

    check_access("/etc/passwd");
    check_access("/etc/shadow");
    check_access("/usr/bin/ls");
    return 0;
}