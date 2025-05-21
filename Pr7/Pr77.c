#include <stdio.h>
#include <stdlib.h>
#include <time.h>
double rand_0_to_1() {
    return (double)rand() / RAND_MAX;
}
double rand_0_to_n(double n) {
    return rand_0_to_1() * n;
}
int main() {
    srand(time(NULL));
    printf("0.0 and 1.0:\n");
    for (int i = 0; i < 5; i++) {
        printf("%.4f\n", rand_0_to_1());
    }
    double n = 5.5;
    printf("\n 0.0 and %.1f:\n", n);
    for (int i = 0; i < 5; i++) {
        printf("%.4f\n", rand_0_to_n(n));
    }
    return 0;
}