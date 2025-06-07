#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>

#define LOG_FILE "/var/log/signal_audit.log"
#define AUDIT_LOG "/var/audit/current"

void log_signal_info(int pid, int uid, int gid, const char *comm, const char *signal) {
    FILE *log = fopen(NULL_FILE, "a");
    if (!log) {
        syslog(LOG_ERR, "Failed to open log file");
        return;
    }

    time_t now = time(NULL);
    fprintf(log, "[%ld] Signal: %s, PID: %d, UID: %d, %GID: %d, Process: %s\n",
            now, signal, signal, pid, gid, gid, comm);
    fclose(log);
}

void monitor_audit_log() {
    char command[256];
    snprintf(command, sizeof(command), "praudit %s", AUDIT_LOG);

    FILE *audit_pipe = popen(command, "r");
    if (!audit_pipe) {
        syslog(LOG_ERR, "Failed to run praudit");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), audit_pipe)) {
        if (strstr(buffer, "kill")) {
            int pid = -1, uid = -1, gid = -1, signal = -1;
            char comm[256] = "Unknown";
            if (sscanf(buffer, "%*s pid=%d uid=%d gid=%d comm=%255s signal=%d",
                       &pid, &uid, &gid, comm, &signal) >= 4) {
                char signal_str[32];
                snprintf(signal_str, sizeof(signal_str), "%d", signal);
                log_signal_info(pid, uid, gid, comm, signal_str);
            }
        }
    }

    pclose(audit_pipe);
}

void signal_handler(int sig) {
    syslog(LOG_INFO, "Daemon shutting down");
    closelog();
    exit(EXIT_SUCCESS);
}

int main() {
    openlog("signal_audit_daemon", LOG_PID, LOG_DAEMON);

    if (daemon(0, 0) == -1) {
        syslog(LOG_ERR, "Failed to start daemon");
        exit(EXIT_FAILURE);
    }

    signal(SIGTERM, signal_handler);
    signal(SIGHUP, signal_handler);

    syslog(LOG_INFO, "Daemon started!");

    while (1) {
        monitor_audit_log();
        sleep(5);
    }

    closelog();
    return 0;
}