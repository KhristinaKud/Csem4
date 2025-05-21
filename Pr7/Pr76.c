#include <stdio.h>
#include <sys/time.h>

double measure_time() {
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (volatile long i = 0; i < 100000000; i++);
    gettimeofday(&end, NULL);
    return (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;
}

int main() {
    double ms = measure_time();
    printf("Execution time: %.2f ms\n", ms);
    return 0;
}