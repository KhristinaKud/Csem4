#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <syslog.h>
#include <errno.h>
#include <libproc.h>

#define LOG_FILE "/var/log/signal_daemon.log"

void daemonize(void);
void signal_handler(int sig, siginfo_t *si, void *uc);
void log_signal(int sig, pid_t pid, uid_t uid, gid_t gid, const char *proc_name);

int main(void) {
    daemonize();

    openlog("signal_daemon", LOG_PID | LOG_CONS, LOG_DAEMON);
    syslog(LOG_INFO, "Signal daemon started");

    struct sigaction sa;
    sa.sa_sigaction = signal_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    // Налаштування обробки всіх можливих сигналів
    for (int i = 1; i < NSIG; i++) {
        if (i != SIGKILL && i != SIGSTOP) { // SIGKILL і SIGSTOP не можна перехопити
            if (sigaction(i, &sa, NULL) == -1) {
                syslog(LOG_ERR, "Failed to set handler for signal %d: %s", i, strerror(errno));
            }
        }
    }

    // Безкінечний цикл для роботи демона
    while (1) {
        pause();
    }

    closelog();
    return 0;
}

void daemonize(void) {
    pid_t pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    if (setsid() < 0) {
        exit(EXIT_FAILURE);
    }

    // Закриття стандартних дескрипторів
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Відкриття /dev/null для stdin, stdout, stderr
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_WRONLY);
    open("/dev/null", O_WRONLY);

    // Встановлення прав доступу до файлів
    umask(027);
}

void signal_handler(int sig, siginfo_t *si, void *uc) {
    char proc_name[256] = "unknown";
    pid_t pid = si->si_pid;
    uid_t uid = si->si_uid;
    gid_t gid = getgid(); // Отримуємо GID процесу-демона

    // Отримання імені процесу за PID
    char path[256];
    snprintf(path, sizeof(path), "/proc/%d/comm", pid);
    int fd = open(path, O_RDONLY);
    if (fd != -1) {
        ssize_t n = read(fd, proc_name, sizeof(proc_name) - 1);
        if (n > 0) {
            proc_name[n - 1] = '\0'; // Видаляємо '\n'
        }
        close(fd);
    }

    log_signal(sig, pid, uid, gid, proc_name);
}

void log_signal(int sig, pid_t pid, uid_t uid, gid_t gid, const char *proc_name) {
    FILE *log = fopen(LOG_FILE, "a");
    if (!log) {
        syslog(LOG_ERR, "Failed to open log file: %s", strerror(errno));
        return;
    }

    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0'; // Видаляємо '\n'

    fprintf(log, "[%s] Signal: %d, PID: %d, UID: %d, GID: %d, Process: %s\n",
            time_str, sig, pid, uid, gid, proc_name);
    fclose(log);

    syslog(LOG_INFO, "Signal: %d, PID: %d, UID: %d, GID: %d, Process: %s",
           sig, pid, uid, gid, proc_name);
}