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
    FILE *log = fopen(LOG_FILE, "a");
    if (!log) {
        syslog(LOG_ERR, "Failed to open log file");
        return;
    }

    time_t now = time(NULL);
    fprintf(log, "[%ld] Signal: %s, PID: %d, UID: %d, GID: %d, Process: %s\n",
            now, signal, pid, uid, gid, comm);
    fclose(log);
}

// Function to read audit logs
void monitor_audit_log() {
    FILE *audit_file = fopen(AUDIT_LOG, "r");
    if (!audit_file) {
        syslog(LOG_ERR, "Failed to open audit log");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), audit_file)) {
        printf("Audit log: %s\n", buffer);
    }

    fclose(audit_file);
}

int main() {
    openlog("signal_audit_daemon", LOG_PID, LOG_DAEMON);

    if (daemon(0, 0) == -1) {
        syslog(LOG_ERR, "Failed to start daemon");
        exit(EXIT_FAILURE);
    }

    syslog(LOG_INFO, "Daemon started!");

    while (1) {
        monitor_audit_log();
        sleep(5);
    }

    closelog();
    return 0;
}
