#include "protocol.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>

struct player *players;

void handle_signal(int sig) {
    if (sig == SIGUSR1) for (int i = 0; i < NUM; i++) printf("Player: %s, Score: %d\n", players[i].player_name, players[i].score);
    printf("----------------------------------------\n");
}

int main() {
    int fd = shm_open(NAME, O_RDONLY | O_CREAT, 0666);
    if (fd < 0) {perror("shm_open()"); return EXIT_FAILURE;}

    void *data = mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (data == (void *)-1) {perror("mmap()"); return EXIT_FAILURE;}

    players = (struct player *)data;
    printf("Viewer PID: %d\n", getpid());

    signal(SIGUSR1, handle_signal);
    while (1) pause();

    munmap(data, SIZE);
    close(fd);

    return EXIT_SUCCESS;
}
