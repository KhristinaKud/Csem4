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
void log_signal_info(int pid, int uid, int gid, const char *comm, const char *signal) {
    FILE *log = fopen(LOG_FILE, "a");
    if (!log) {
        syslog(LOG_ERR, "Failed to open log file: %s", strerror(errno));
        return;
    }
#include <syslog.h>

    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0'; // Видаляємо \n
volatile sig_atomic_t keep_running = 1;

    fprintf(log, "[%s] Signal: %s, PID: %d, UID: %d, GID: %d, Process: %s\n",  time_str, signal, pid, uid, gid, comm);
    fclose(log);
void handle_shutdown(int sig) {
    keep_running = 0;
}

int main(void) {
int main() {
    int audit_fd;
    struct audit_message rep;
    char *signal_info;
    openlog("signal_audit_daemon", LOG_PID, LOG_DAEMON);
    if (daemon(0, 0) == -1) {
        syslog(LOG_ERR, "Failed to daemonize: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    struct audit_message msg;
    openlog("signal_audit", LOG_PID, LOG_DAEMON);
    syslog(LOG_INFO, "Starting signal audit daemon");
    signal(SIGINT, handle_shutdown);
    signal(SIGTERM, handle_shutdown);

    audit_fd = audit_open();
    if (audit_fd < 0) {
        syslog(LOG_ERR, "Failed to open audit netlink socket: %s", strerror(errno));
        exit(EXIT_FAILURE);
        syslog(LOG_ERR, "Failed to open audit netlink");
        closelog();
        exit(1);
    }
    if (audit_set_pid(audit_fd, getpid(), WAIT_YES) < 0) {
        syslog(LOG_ERR, "Failed to set audit PID: %s", strerror(errno));

    if (audit_set_enabled(audit_fd, 1) < 0) {
        syslog(LOG_ERR, "Failed to enable audit");
        audit_close(audit_fd);
        exit(EXIT_FAILURE);
        closelog();
        exit(1);
    }
    struct audit_rule_data *rule = calloc(1, sizeof(struct audit_rule_data));
    if (!rule) {
        syslog(LOG_ERR, "Failed to allocate memory for audit rule");
        audit_close(audit_fd);
        exit(EXIT_FAILURE);
    }
    if (audit_add_rule_data(audit_fd, rule, AUDIT_FILTER_EXIT, AUDIT_ALWAYS) < 0) {
        syslog(LOG_ERR, "Failed to add audit rule: %s", strerror(errno));
    audit_rule_syscallbyname_data(rule, "kill");
    if (audit_add_rule(audit_fd, rule, AUDIT_FILTER_EXIT, AUDIT_ALWAYS) < 0) {
        syslog(LOG_ERR, "Failed to add audit rule");
        free(rule);
        audit_close(audit_fd);
        exit(EXIT_FAILURE);
        closelog();
        exit(1);
    }

    free(rule);

    while (1) {
        if (audit_get_reply(audit_fd, &rep, GET_REPLY_BLOCKING, 0) < 0) {
            syslog(LOG_ERR, "Failed to get audit reply: %s", strerror(errno));
            continue;
    while (keep_running) {
        if (audit_get_reply(audit_fd, &msg, GET_REPLY_BLOCKING, 0) < 0) {
            syslog(LOG_ERR, "Failed to get audit reply");
            break;
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
        if (msg.nlh && msg.data) {
            char *data = msg.data;
            pid_t pid = 0;
            uid_t uid = 0;
            gid_t gid = 0;
            char comm[256] = {0};
            sscanf(data, "pid=%d uid=%d gid=%d comm=%255s", &pid, &uid, &gid, comm);
            syslog(LOG_INFO, "Signal detected: PID=%d, UID=%d, GID=%d, Process=%s",  pid, uid, gid, comm);
        }

        free(msg.data);
        msg.data = NULL;
    }
    audit_delete_rule(audit_fd, rule, AUDIT_FILTER_EXIT, AUDIT_ALWAYS);
    free(rule);
    audit_close(audit_fd);
    syslog(LOG_INFO, "Signal audit daemon stopped");
    closelog();

    return 0;
}