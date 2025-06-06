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
#include <libproc.h>
#define LOG_FILE "/var/log/signal_daemon.log"
char* get_process_name(pid_t pid) {
    static char proc_name[256];
    char path[256];
    snprintf(path, sizeof(path), "/proc/%d/comm", pid);
    FILE *fp = fopen(path, "r");
    if (fp) {
        if (fgets(proc_name, sizeof(proc_name), fp)) {
            proc_name[strcspn(proc_name, "\n")] = 0; // Remove newline character
        } else {
            strcpy(proc_name, "unknown");
        }
        fclose(fp);
    } else {
        strcpy(proc_name, "unknown");
    }
    return proc_name;
}
void signal_handler(int sig, siginfo_t *si, void *unused) {
    FILE *log = fopen(LOG_FILE, "a");
    if (!log) {
        syslog(LOG_ERR, "Failed to open log file");
        return;
    }
    time_t now;
    time(&now);
    char *time_str = ctime(&now);
    time_str[strlen(time_str)-1] = '\0';
    struct proc_bsdinfo proc;
    int ret = proc_pidinfo(si->si_pid, PROC_PIDTBSDINFO, 0, &proc, sizeof(proc));
    uid_t uid = (ret > 0) ? proc.pbi_uid : si->si_uid;
    gid_t gid = (ret > 0) ? proc.pbi_gid : si->si_gid;

    fprintf(log, "[%s] Signal: %d, PID: %d, UID: %d, GID: %d, Process: %s\n",
            time_str, sig, si->si_pid, uid, gid, get_process_name(si->si_pid));

    fclose(log);
}

void setup_signals() {
    struct sigaction sa;
    sa.sa_sigaction = signal_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    for (int i = 1; i < NSIG; i++) {
        if (i != SIGKILL && i != SIGSTOP) {
            sigaction(i, &sa, NULL);
        }
    }
}

int main() {

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
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    openlog("signal_daemon", LOG_PID, LOG_DAEMON);

    setup_signals();

    FILE *log = fopen(LOG_FILE, "w");
    if (!log) {
        syslog(LOG_ERR, "Failed to create log file");
        exit(EXIT_FAILURE);
    }
    fclose(log);

    while (1) {
        pause();
    }

    closelog();
    return 0;
}
