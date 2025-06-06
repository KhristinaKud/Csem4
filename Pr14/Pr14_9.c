#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <seconds>\n", argv[0]);
        return 1;
    }

    long seconds = atol(argv[1]);
    if (seconds <= 0) {
        fprintf(stderr, "Please provide a positive number of seconds\n");
        return 1;
    }

    struct timespec ts;
    ts.tv_sec = seconds;
    ts.tv_nsec = 0;

    if (clock_nanosleep(CLOCK_MONOTONIC, 0, &ts, NULL) != 0) {
        perror("clock_nanosleep failed");
        return 1;
    }

    printf("Timer finished after %ld seconds!\n", seconds);
    return 0;
}
