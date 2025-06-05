#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Trying to read /etc/shadow:\n");
    int result = system("sudo cat /etc/shadow");
    if (result == -1) {
        perror("Execution error sudo cat /etc/shadow");
        return 1;
    } else if (result != 0) {
        printf("The team ended because there were not enough rights \n");
        return 1;
    }
    return 0;
}