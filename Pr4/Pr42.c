#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int a = -1;
    void *ptr = malloc(a);
    if (ptr == NULL) {
        printf("malloc cannot allocate memory for a negative size\n");
    } else {
        printf("malloc can allocate memory for negative size\n");
        free(ptr);
    }

    long xa = LONG_MAX;
    printf("xa = %ld\n", xa);
    int xb = 2;
    int num = xa * xb;
    printf("num = %d\n", num);
    void *ptr2 = malloc(num);
    if (ptr == NULL) {
        printf("malloc failed\n");
    } else {
        printf("Allocated %d bytes\n", num);
        free(ptr);
    }

    return 0;
}
