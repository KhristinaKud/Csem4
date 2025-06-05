#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf(" whoami:\n");
    if (system("whoami") != 0) {
        perror("Whoami execution error");
        return 1;
    }
    printf("\n id:\n");
    if (system("id") != 0) {
        perror("Runtime error id");
        return 1;
    }

    return 0;
}