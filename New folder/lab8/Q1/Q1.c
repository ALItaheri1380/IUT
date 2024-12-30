#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>

#define MAXCHILD 5

void sleep_custm(int r)
{
    struct timeval start_time,end_time;
    srand(time(NULL));
    gettimeofday(&start_time,NULL);
    while (true)
    {
        gettimeofday(&end_time,NULL);
        if ((end_time.tv_usec - start_time.tv_usec)/1000 + (end_time.tv_sec - start_time.tv_sec)*1000 > r*1000) return;
    }
}

void task(int id)
{
    srand(time(NULL)+getpid());
    int tm = rand() % 5 + 1;
    sleep_custm(tm);
    printf("Task %d has been done by child %d in %d seconds\n", id, getpid(), tm);
    exit(0);
}

int main(void)
{
    pid_t Children [MAXCHILD]; int status = 0;

    for(int i = 0; i < MAXCHILD; i++)
    {
        pid_t pid = fork();

        if (!pid) task(i);
        else if (pid < 0){perror("\nfork failed\n"); exit(1);}
        else Children[i] = pid;
    }

    while(true)
    {
        sleep(5);
        printf("===============================================\n");
        for (int i = 0; i < MAXCHILD; i++) {
            pid_t pid = waitpid(Children[i], &status, WUNTRACED | WNOHANG);

            if (!pid) printf("Child %d is still running\n", Children[i]);
            else if (pid < 0) perror("waitpid is failed\n");
            else{
                if (WIFEXITED(status))		  {Children[i] = fork(); if (!Children[i]) task(i);}
	            else if (WIFSIGNALED(status)) printf("child process exited due to signal %d\n", WTERMSIG(status));
	            else if (WIFSTOPPED(status))  printf("child process was stopped by signal %d\n", WSTOPSIG(status));
            }
        }
    }
    return 0;
}