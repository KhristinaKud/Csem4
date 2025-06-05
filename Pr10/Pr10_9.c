#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_CHILDREN 10

int main() {
    pid_t pids[NUM_CHILDREN];
    for (int i = 0; i < NUM_CHILDREN; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("fork failed");
            return 1;
        }
        else if (pids[i] == 0) {
            printf("Child process %d, PID: %d\n", i+1, getpid());
            return 0;
        }
    }
    for (int i = 0; i < NUM_CHILDREN; i++) {
        wait(NULL);
    }
    printf("All child processes have been completed.\n");
    return 0;
}