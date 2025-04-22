#include <stdio.h>

void recursiveFunction(int depth) {
    printf("Recursion depth: %d\n", depth);
    recursiveFunction(depth + 1);
}

int main() {
    recursiveFunction(1);
    return 0;
}
