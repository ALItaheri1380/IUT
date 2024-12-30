#include "protocol.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    int fd = shm_open(NAME, O_CREAT | O_RDWR, 0600);
    if (fd < 0)
    {
        perror("shm_open()");
        return EXIT_FAILURE;
    }
    ftruncate(fd, SIZE);

    void *data = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == (void *)-1)
    {
        perror("mmap()");
        return EXIT_FAILURE;
    }
    struct player *players = (struct player *)data;

    for (int i = 0; i < NUM; i++)
    {
        snprintf(players[i].player_name, STR_L, "ali %d", i + 1);
        players[i].score = rand() % 100 + 1;
    }

    munmap(data, SIZE);
    close(fd);

    return EXIT_SUCCESS;
}