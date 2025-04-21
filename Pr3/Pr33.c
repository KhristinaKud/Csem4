#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1024  // Максимальний розмір файлу у байтах
void roll() {
    FILE *file = fopen("texttask3", "w");
    if (!file) {
        printf("File could not be opened for writing.\n");
        return;
    }
    srand(time(NULL));
    long file_size = 0;
    while (file_size < MAX_SIZE) {
        int roll = rand() % 6 + 1;
        fprintf(file, "%d\n", roll);
        fflush(file);

        file_size = ftell(file);
        if (file_size >= MAX_SIZE) {
            printf("File size limit reached.\n");
            break;
        }
    }
    fclose(file);
}

int main() {
    roll();
    return 0;
}
