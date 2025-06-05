#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>


void check_file_access(const char *filename) {
    if (access(filename, R_OK) == 0) {
        printf("The file is available for reading\n");
    } else {
        perror("The file is unreadable");
    }

    if (access(filename, W_OK) == 0) {
        printf("The file is available for writing\n");
    } else {
        perror("The file is not writable");
    }
}
int main() {
    char *filename = "testfile.txt";
    char cmd[256];
    printf("The user's UID:%d\n", getuid());
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error");
        return 1;
    }
    fprintf(fp, "Hello user, hello world, mama mama papa papa \n");
    fclose(fp);

    snprintf(cmd, sizeof(cmd), "sudo chown root:root %s", filename);
    if (system(cmd) != 0) {
        fprintf(stderr, "Error changing owner\n");
        return 1;
    }

    snprintf(cmd, sizeof(cmd), "sudo chmod 600 %s", filename);
    if (system(cmd) != 0) {
        fprintf(stderr, "Error changing permissions\n");
        return 1;
    }
    check_file_access(filename);

    snprintf(cmd, sizeof(cmd), "sudo rm %s", filename);
    if (system(cmd) != 0) {
        fprintf(stderr, "File deletion error\n");
    }

    return 0;
}