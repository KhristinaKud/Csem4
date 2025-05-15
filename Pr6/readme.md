# Практична 6.9
## Умова завдання
Test Case #9: Use-after-return. Поверніть адресу локальної змінної з функції.
## Приклад Завдання
В лекції був код 
```text
int *get_ptr() {
    int x = 5;
    return &x;  // UAR (pointer to stack memory)
}
int main() {
    int *ptr = get_ptr();
    printf("%d", *ptr);  // Undefined behavior!
    return 0;
}
```
на основі цього коду зробимо правильну програму 
## Компіляція 
```bash
kristi @host:~/Downloads $ gcc -WaII Pr6.c -0 Pr5 
kristi @host:~/Downloads $/Pr6
```
## Результати Компіляції 
```text
5
```
## Пояснення 
Я обрала виправлення цієї задачі через динамічну пам'ять, тому що вона гарантує, що дані існуватимуть, доки їх явно не звільнять через free(). Як бачимо програма працює коректно.
