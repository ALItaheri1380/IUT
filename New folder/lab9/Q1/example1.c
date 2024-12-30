#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CHILD 5  

long long answer = 1; 

void fct(int inp, int i, int pipe_fd[2]) {

    close(pipe_fd[0]);

    int range_size = inp / MAX_CHILD;
    int start = i * range_size + 1;
    int end = (i == MAX_CHILD - 1) ? inp : (i + 1) * range_size;

    long long result = 1;
    for (int j = start; j <= end; j++) result *= j;

    printf("child-%d: %lld\n", i + 1, result);
    write(pipe_fd[1], &result, sizeof(result));
    exit(0);
}

int main() {
    int inp; 
    scanf("%d", &inp);
    if (inp >  20 || inp < 1){perror("invalid input"); return 1;}
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    for (int i = 0; i < MAX_CHILD; i++) {
        pid_t pid = fork();
        if (pid == 0)  fct(inp, i, pipe_fd);
    }

    close(pipe_fd[1]);

    for (int i = 0; i < MAX_CHILD; i++) {
        long long child_result;
        read(pipe_fd[0], &child_result, sizeof(child_result));
        answer *= child_result;
    }
    for(int i =0 ; i < MAX_CHILD; i++) wait(NULL);
    printf("factorial of %d is = %lld\n", inp, answer);   

    return 0;
}
