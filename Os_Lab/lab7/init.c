#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <string.h>

struct process_info {
    char state[16];
    unsigned long memory_usage;
    char process_name[32];
};

int main(void) {
    pid_t pid;
    struct process_info info;

    while (1) {
        printf("========================================\n");
        printf(" Enter Process ID (PID): ");
        scanf("%d", &pid);
        printf("----------------------------------------\n");

        long result = syscall(548, pid, &info);

        if (result == -1) {
            perror("Error: Unable to fetch process details");
            printf("========================================\n");
            exit(EXIT_FAILURE);
        }

        printf("\n");
        printf(" Process Information:\n");
        printf(" ----------------------------------------\n");
        printf(" %-20s : %d\n", "Process ID (PID)", pid);
        printf(" %-20s : %s\n", "Process Name", info.process_name);
        printf(" %-20s : %s\n", "State", info.state);
        printf(" %-20s : %lu bytes\n", "Memory Usage", info.memory_usage);
        printf(" ----------------------------------------\n");
        printf("\n");

        printf("========================================\n\n");

        sleep(1);
    }

    return 0;
}
