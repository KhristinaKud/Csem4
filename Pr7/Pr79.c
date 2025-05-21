#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IP_LEN 16
#define MAX_PORTS 65535

int main() {
    char target_ip[MAX_IP_LEN];
    int start_port, end_port;

    printf("Введіть IP-адресу для сканування: ");
    scanf("%15s", target_ip);

    printf("Введіть початковий порт (1-%d): ", MAX_PORTS);
    scanf("%d", &start_port);
    printf("Введіть кінцевий порт (1-%d): ", MAX_PORTS);
    scanf("%d", &end_port);

    if (start_port < 1 || end_port > MAX_PORTS || start_port > end_port) {
        printf("Некоректний діапазон портів!\n");
        return 1;
    }

    printf("Сканування портів %d-%d на хості %s...\n", start_port, end_port, target_ip);

    char command[256];
    for (int port = start_port; port <= end_port; port++) {
        snprintf(command, sizeof(command), "nc -z -w 1 %s %d", target_ip, port);
        int result = system(command);
        if (result == 0) {
            printf("Порт %d відкритий\n", port);
        }
    }

    return 0;
}