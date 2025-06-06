#include <libaudit.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <syslog.h>

volatile sig_atomic_t keep_running = 1;

void handle_shutdown(int sig) {
    keep_running = 0;
}

int main() {
    int audit_fd;
    struct audit_message msg;
    openlog("signal_audit", LOG_PID, LOG_DAEMON);
    syslog(LOG_INFO, "Starting signal audit daemon");
    signal(SIGINT, handle_shutdown);
    signal(SIGTERM, handle_shutdown);

    audit_fd = audit_open();
    if (audit_fd < 0) {
        syslog(LOG_ERR, "Failed to open audit netlink");
        closelog();
        exit(1);
    }

    if (audit_set_enabled(audit_fd, 1) < 0) {
        syslog(LOG_ERR, "Failed to enable audit");
        audit_close(audit_fd);
        closelog();
        exit(1);
    }
    struct audit_rule_data *rule = calloc(1, sizeof(struct audit_rule_data));
    audit_rule_syscallbyname_data(rule, "kill");
    if (audit_add_rule(audit_fd, rule, AUDIT_FILTER_EXIT, AUDIT_ALWAYS) < 0) {
        syslog(LOG_ERR, "Failed to add audit rule");
        free(rule);
        audit_close(audit_fd);
        closelog();
        exit(1);
    }
    while (keep_running) {
        if (audit_get_reply(audit_fd, &msg, GET_REPLY_BLOCKING, 0) < 0) {
            syslog(LOG_ERR, "Failed to get audit reply");
            break;
        }
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