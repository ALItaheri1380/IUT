#include "protocol.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX_CHILD 5

int main(int argc, char *argv[]) {
    pid_t viewer_pid = atoi(argv[1]);
    int fd = shm_open(NAME, O_CREAT | O_RDWR, 0600);
    if (fd < 0) { perror("shm_open()"); return EXIT_FAILURE;}

    ftruncate(fd, SIZE);

    void *data = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == (void *)-1) {perror("mmap()"); return EXIT_FAILURE;}

    struct player *players = (struct player *)data;

    while (1) {
        pid_t child_pids[MAX_CHILD];

        for (int child_id = 0; child_id < MAX_CHILD; child_id++) {
            pid_t pid = fork();
            if (pid == 0) {
            	srand(time(NULL) + getpid());
                for (int i = child_id; i < NUM; i += MAX_CHILD) {
                    snprintf(players[i].player_name, STR_L, "ali %d", i + 1);
                    players[i].score = rand() % 100 + 1;
                }
                munmap(data, SIZE);
                close(fd);
                exit(EXIT_SUCCESS);
            } else if(pid > 0) child_pids[child_id] = pid;
        }
        for (int child_id = 0; child_id < MAX_CHILD; child_id++) waitpid(child_pids[child_id], NULL, 0);

        printf("Updated!\n");
        kill(viewer_pid, SIGUSR1);
        sleep(3);
    }

    munmap(data, SIZE);
    close(fd);

    return EXIT_SUCCESS;
}
