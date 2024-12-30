#include "protocol.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
    int fd = shm_open(NAME, O_RDONLY, 0666);
    if (fd < 0)
    {
        perror("shm_open()");
        return EXIT_FAILURE;
    }

    void *data = mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (data == (void *)-1)
    {
        perror("mmap()");
        return EXIT_FAILURE;
    }

    struct player *players = (struct player *)data;

    printf("Receiver address: %p\n", data);

    for (int i = 0; i < NUM; i++)
        printf("Player name: %s, Score: %d\n", players[i].player_name, players[i].score);

    munmap(data, SIZE);
    close(fd);

    shm_unlink(NAME);

    return EXIT_SUCCESS;
}