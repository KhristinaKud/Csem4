# Завдання 5.9
## Опис завдання 
Побудуйте тест, де дві змінні випадково використовують ту саму адресу пам’яті (через обхід типів) — і виявити це можливо лише за допомогою логування.

## Компіляція
```bash
kristi @host:~/Downloads $ gcc Wa II Pr5.c -0 Pr5 
kristi @host:~/Downloads $/Pr5 
```
## Результат компіляції 
```text
[LOG] Address of a: 0x820a8384c, value: 10 
[LOG] Address of b: 0x820a83848, value: 0.000000 
[LOG] After changing a to 100: 
[LOG] a: 100, b: 0.000000
```
## Пояснення 
Логування - це процес запису інформації про роботу програми під час її виконання.
Ця програма маніпулює пам’яттю, змінюючи значення змінної b типу float через приведення типів із int. Тобто  адреса змінної b змінюємо як адресу типу int і присвоюємо їй значення змінної a. Таке присвоєння є небезпечним, бо змінна b, за своїм визначенням, має містити число з плаваючою комою, а їй було присвоєно ціле число. В результаті b використовує ту саму область пам’яті, що й a. Це викликає некоректне трактування даних, адже b розрахована на інший формат. Логування показує що адреси a і b різні (компілятор може розмістити їх окремо), але значення b "зіпсується", бо воно інтерпретується як float, хоча в пам’яті лежить int.
