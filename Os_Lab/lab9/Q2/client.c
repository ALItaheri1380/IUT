#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FIFO_PATH "/tmp/temperature_pipe"

typedef struct {
    pid_t pid;        
    int temperature; 
} TemperatureData;

int main() {
    int fifo_fd, min_data;
    TemperatureData temp_data;


    temp_data.pid = getpid();
    srand(time(NULL) + getpid());

    while (1) {

        temp_data.temperature = (rand() % 41);

        fifo_fd = open(FIFO_PATH, O_WRONLY);
        if (fifo_fd < 0) { perror("error opening FIFO for writing"); exit(1); }
        write(fifo_fd, &temp_data, sizeof(temp_data));
        close(fifo_fd);
        printf("PID: %d | temperature Sent: %d\n", temp_data.pid, temp_data.temperature);
        fifo_fd = open(FIFO_PATH, O_RDONLY);
        if (fifo_fd == -1) { perror("error opening FIFO for reading"); exit(1); }
        read(fifo_fd, &min_data, sizeof(min_data));
        close(fifo_fd);
        printf("--------------------------------------\n");
        printf("min temperature value is = %d\n", min_data);
        printf("--------------------------------------\n");
        sleep(3);
    }

    return 0;
}

