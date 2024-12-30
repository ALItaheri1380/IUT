#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>

void handle_sigint(int signal) {printf("\nprogram terminated by SIGINT.\n"); exit(0); }
void handle_sigterm(int signal) {printf("\nprogram received termination SIGTERM.\n"); exit(0);}

void get_custom_time(char *time_str, char *date_str, size_t size) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    snprintf(time_str,size,"%02d:%02d:%02d",tm->tm_hour,tm->tm_min,tm->tm_sec);
    snprintf(date_str,size,"%04d-%02d-%02d",tm->tm_year + 1900,tm->tm_mon + 1,tm->tm_mday);
}

int main() {
    struct timeval start_time, stop_time;

    signal(SIGINT, handle_sigint);
    signal(SIGTERM, handle_sigterm);

    printf("═════════════════════════════════════════════════════════════════════════\n");
    printf("│ %-12s │ %-10s │ %-20s │ %-10s \n", "DATE", "TIME", "EXECUTION TIME (ms)", "ARGUMENT");
    printf("═════════════════════════════════════════════════════════════════════════\n");

    while (1) {
        int r = rand() % 5 + 1;
        int status = 0;

        pid_t pid = fork();
        gettimeofday(&start_time, NULL);

        if (pid == 0) {
            execl("./app", "app", (char[2]){r + '0', '\0'}, NULL);
            perror("Error executing execl");
            exit(1);
        }
        
        else if (pid > 0) {
            wait(&status);
            gettimeofday(&stop_time, NULL);
            char time_str[200] , date_str[200];

            get_custom_time(time_str, date_str, sizeof(time_str));

            long elapsed = (stop_time.tv_usec - start_time.tv_usec) / 1000 + (stop_time.tv_sec - start_time.tv_sec) * 1000;

            printf("│ %-12s │ %-10s │ %-20ld │ %-10d \n", date_str, time_str, elapsed, r);
            printf("═════════════════════════════════════════════════════════════════════════\n");
        } 
        
        else {perror("fork failed"); exit(1); }

    }

    return 0;
}
