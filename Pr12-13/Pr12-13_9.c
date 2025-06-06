#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>
#include <libaudit.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>

#define LOG_FILE "/var/log/signal_audit.log"

// Функція для запису в лог-файл
void log_signal_info(int pid, int uid, int gid, const char *comm, const char *signal) {
    FILE *log = fopen(LOG_FILE, "a");
    if (!log) {
        syslog(LOG_ERR, "Failed to open log file: %s", strerror(errno));
        return;
    }

    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0'; // Видаляємо \n

    fprintf(log, "[%s] Signal: %s, PID: %d, UID: %d, GID: %d, Process: %s\n",  time_str, signal, pid, uid, gid, comm);
    fclose(log);
}

int main(void) {
    int audit_fd;
    struct audit_message rep;
    char *signal_info;
    openlog("signal_audit_daemon", LOG_PID, LOG_DAEMON);
    if (daemon(0, 0) == -1) {
        syslog(LOG_ERR, "Failed to daemonize: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    audit_fd = audit_open();
    if (audit_fd < 0) {
        syslog(LOG_ERR, "Failed to open audit netlink socket: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (audit_set_pid(audit_fd, getpid(), WAIT_YES) < 0) {
        syslog(LOG_ERR, "Failed to set audit PID: %s", strerror(errno));
        audit_close(audit_fd);
        exit(EXIT_FAILURE);
    }
    struct audit_rule_data *rule = calloc(1, sizeof(struct audit_rule_data));
    if (!rule) {
        syslog(LOG_ERR, "Failed to allocate memory for audit rule");
        audit_close(audit_fd);
        exit(EXIT_FAILURE);
    }
    if (audit_add_rule_data(audit_fd, rule, AUDIT_FILTER_EXIT, AUDIT_ALWAYS) < 0) {
        syslog(LOG_ERR, "Failed to add audit rule: %s", strerror(errno));
        free(rule);
        audit_close(audit_fd);
        exit(EXIT_FAILURE);
    }

    free(rule);

    while (1) {
        if (audit_get_reply(audit_fd, &rep, GET_REPLY_BLOCKING, 0) < 0) {
            syslog(LOG_ERR, "Failed to get audit reply: %s", strerror(errno));
            continue;
        }
     if (rep.nlh->nlmsg_type == AUDIT_SIGNAL_INFO) {
            signal_info = (char *)rep.data;
            int pid = 0, uid = 0, gid = 0;
            char comm[AUDIT_MAX_SIGNAL_INFO_LEN] = {0};
            char signal[16] = {0};
            sscanf(signal_info, "pid=%d uid=%d gid=%d comm=\"%[^\"]\" sig=%s",&pid, &uid, &gid, comm, signal);
            log_signal_info(pid, uid, gid, comm, signal);
        }
        if (rep.data) {
            free(rep.data);
            rep.data = NULL;
        }
    }
    audit_close(audit_fd);
    closelog();
    return 0;
}