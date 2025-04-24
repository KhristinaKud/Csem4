#include <stdio.h>
#include <stdint.h>

int main() {
    int a = 10;
    float b;


    *(int*)&b = a;  // Тепер b "використовує" ту саму пам'ять, що й a

    // Логування адрес та значень
    printf("[LOG] Address of a: %p, value: %d\n", (void*)&a, a);
    printf("[LOG] Address of b: %p, value: %f\n", (void*)&b, b);

    // Зміна однієї змінної вплине на іншу?
    a = 100;
    printf("[LOG] After changing a to 100:\n");
    printf("[LOG] a: %d, b: %f\n", a, b);

    return 0;
}