#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *pipe = popen("rwho | more", "r");
    if (!pipe) {
        perror("popen failed");
        return EXIT_FAILURE;
    }

    pclose(pipe);
    return EXIT_SUCCESS;
}