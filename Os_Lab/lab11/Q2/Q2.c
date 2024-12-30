#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdbool.h>

int *readCount = 0, *source = 0;
sem_t *readSem, *sourceSem;

void write_task(int id){
    srand(time(NULL) + id);
    while(true){
        printf("writer %d wants to write.\n", id);
        sem_wait(sourceSem);
        *source = *source + 1;
        printf("writer %d write value %d to shared mem.\n", id, *source);
        int t = rand()%3 + 1; sleep(t);
        sem_post(sourceSem);
        t = rand()%3 + 1; sleep(t);
    }
}

void read_task(int id){
    srand(time(NULL) + id);
    while(true){
        printf("Reader %d wants to read \n", id);
        sem_wait(readSem);
        if(*readCount == 0) sem_wait(sourceSem);
        *readCount = *readCount + 1;
        sem_post(readSem);

        printf("source data = %d \n", *source);
        int t = rand()%3 + 1; sleep(t);

        sem_wait(readSem);
        *readCount = *readCount - 1;
        if(*readCount == 0) sem_post(sourceSem);
        sem_post(readSem);
        t = rand()%3 + 1; sleep(t);
    }
}

int main() {
	
	void *shm = mmap(NULL, 2*sizeof(sem_t)+2*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED| MAP_ANONYMOUS, -1, 0);
	readSem = (sem_t *) shm;
	sourceSem = (sem_t *) (shm+sizeof(sem_t));
	readCount = (int *) (shm+2*sizeof(sem_t));
	source = (int *) (shm+2*sizeof(sem_t)+sizeof(int));
	// 1. Initialize the semaphores
    sem_init(readSem,1,1);
    sem_init(sourceSem,1,1);
	// 2. Create child processes and call (reader, writer) functions
    int num_readres, num_writres, tl = 0;
    printf("input num of readers = ");
    scanf("%d",&num_readres);
    printf("input num of writres = ");
    scanf("%d",&num_writres);
    tl = num_readres + num_writres;

    for(int i = 0 ; i < num_readres; i++){
        pid_t pid = fork();
        if(! pid) {read_task(i); exit(0);}

    }

    for(int i = 0 ; i < num_writres ; i++){
        pid_t pid = fork();
        if(! pid) {write_task(i); exit(0);}
    }

    for(int i = 0 ; i < tl ; i++) wait(NULL);
	// 3. Destroy the semaphores
    sem_destroy(readSem);
    sem_destroy(sourceSem);

	munmap(shm, 2*sizeof(sem_t)+2*sizeof(int));
		
}
