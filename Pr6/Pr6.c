#include <stdio.h>
int *get_ptr() {
    int x = 5;
    return &x;
}
int main() {
    int *ptr = get_ptr();
    printf("%d", *ptr);
    return 0;
}
