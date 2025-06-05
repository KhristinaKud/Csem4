#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    char *filename = "testfile.txt";
    char *copy_filename = "/tmp/testfile.txt";
    uid_t user_uid = getuid();
    char cmd[256];

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return 1;
    }
    fprintf(fp, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
    fclose(fp);

    snprintf(cmd, sizeof(cmd), "sudo cp %s %s", filename, copy_filename);
    if (system(cmd) != 0) {
        fprintf(stderr, "File copy error \n");
        return 1;
    }
    printf("File copied \n");
    
    fp = fopen("testfile_copy.txt", "a");
    if (fp == NULL) {
        perror("Error opening file for writing");
        printf("File modification is not possible due to lack of permissions.\n");
    } else {
        fprintf(fp, "Added by user\n");
        fclose(fp);
        printf("File  successfully\n");
    }
    snprintf(cmd, sizeof(cmd), "rm %s", copy_filename);
    if (system(cmd) != 0) {
        fprintf(stderr, "File deletion error (\n");
    } else {
        printf("File %s successfully deleted\n", copy_filename);
    }


    return 0;
}