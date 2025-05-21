#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main() {
    for (int i = 0; i < 7; i++) {
        sleep(1);
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        }
        else if (pid == 0) {
            printf("I am the child %d PID: %d\n",i+1, getpid());
            exit(0);
        }
        else {
            printf("I am the parent %d PID: %d\n",i+1, getpid());
        }
    }
    while (wait(NULL) > 0);
    printf("The finished\n");
    return 0;
}