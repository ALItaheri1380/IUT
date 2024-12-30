#ifndef PROTOCOL_H
#define PROTOCOL_H

#define NAME "/shmem-oslab"
#define NUM 7
#define STR_L 20

struct player {
    char player_name[STR_L];
    int score;
};

#define SIZE (NUM * sizeof(struct player))

#endif