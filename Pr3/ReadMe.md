# Завдання 3.1
## Опис програми 
Запустіть Docker-контейнер і поекспериментуйте з максимальним лімітом ресурсів відкритих файлів. Для цього виконайте команди у вказаному порядку:
```text
$ ulimit -n
$ ulimit -aS | grep "open files"
$ ulimit -aH | grep "open files"
$ ulimit -n 3000
$ ulimit -aS | grep "open files"
$ ulimit -aH | grep "open files"
$ ulimit -n 3001
$ ulimit -n 2000
$ ulimit -n
$ ulimit -aS | grep "open files"
$ ulimit -aH | grep "open files"
$ ulimit -n 3000
```
## Результат Компіляції 
```text
test1@Ubuntu:~$ sudo docker run-it-rm ubuntu bash 
[sudo] password for test1: 
unknown flag: --it 
See 'docker run --help'. 
test1@Ubuntu:~$ ulimit -n 
1024 
test1@Ubuntu:~$ ulimit -as | grep "open files" 
open files                      (-n) 1024 
test1@Ubuntu:~$ ulimit -aH | grep "open files" 
open files                      (-n) 1048576 
test1@Ubuntu:~$ ulimit -n 3000 
test1@Ubuntu:~$ ulimit -as | grep "open files" 
open files                      (-n) 3000 
test1@Ubuntu:~$ ulimit -n 3001 
-bash: ulimit: open files: cannot modify limit: Operation not permitted 
test1@Ubuntu:~$ ulimit -n 2000 
test1@Ubuntu:~$ ulimit -n 
2000 
test1@Ubuntu:~$ ulimit -as | grep "open files" 
open files                      (-n) 2000 
test1@Ubuntu:~$ ulimit -aH | grep "open files" 
open files                      (-n) 2000 
test1@Ubuntu:~$ ulimit -n 3000 
-bash: ulimit: open files: cannot modify limit: Operation not permitted 
```
## Пояснення 
Отже, можна зробити висновок, що зміна лімітів з інтерактивним режимом, можлива тільки у бік зменшення, адже для їх підвищення недостатньо відповідних прав доступу.

---
# Завдання 3.2 
## Опис програми
У Docker-контейнері встановіть утиліту perf(1). Поекспериментуйте з досягненням процесом встановленого ліміту.
## Пояснення 
perf - це  інструмент для аналізу продуктивності в Linux. Він належить до ядра системи і дозволяє детально досліджувати роботу процесорів, пам'яті і т.д.
## Основні можливості perf:
-показує, які процеси найбільше навантажують процесор
-відстежує виділення, використання та помилки пам'яті
 -аналізує, як програми взаємодіють із ядром
Що стосується перевантаження ядра, perf допомагає ідентифікувати програми, що споживають надмірну кількість оперативної пам’яті, CPU.Також виявляє, помилки у коді чи конфігурації системи, які призводять до цього.



