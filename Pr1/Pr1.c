#include <stdio.h>


int replace(char *str, char replacement) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = replacement;
            count++;
        }
    }
    return count;
}

int main() {
    char str[] = "The cat sat";
    char replacement = '-';
    int count = replace(str, replacement);
    printf("Result: \"%s\", Number of replacements: %d\n", str, count);
    return 0;
}