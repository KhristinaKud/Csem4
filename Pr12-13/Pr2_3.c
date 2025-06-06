#include <ucontext.h>
#include <stdio.h>
void handler(int sig, siginfo_t *info, void *context) {
    ucontext_t *uc = (ucontext_t *)context;
#if defined(__x86_64__)
    printf("RIP: %llx\n", (unsigned long long)uc->uc_mcontext.gregs[REG_RIP]);
#endif
}
