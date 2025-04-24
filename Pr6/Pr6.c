#include <stdio.h>
int *get_ptr() {
    int x = 5;
    return &x;  // UAR (pointer to stack memory)
}
int main() {
    int *ptr = get_ptr();
    printf("%d", *ptr);  // Undefined behavior!
    return 0;
}
