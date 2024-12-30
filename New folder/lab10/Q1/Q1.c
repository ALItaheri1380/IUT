#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void sigsegv_handler(int signum, siginfo_t *info, void *context)
{

    printf("segmentation fault at address: %p\n", info->si_addr);
    exit(1);
}

int main()
{

    struct sigaction sa;
    sa.sa_sigaction = sigsegv_handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &sa, NULL);

    int *a = NULL;
    *a = 85;
    return 0;
}
