#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <float.h>
#include <time.h>

#define FIFO_PATH "/tmp/temperature_pipe"

typedef struct {
    pid_t pid;        
    int temperature; 
} TemperatureData;

int main() {
    int fifo_fd, min_temp=2e3;
    TemperatureData temp_data;

    mkfifo(FIFO_PATH, 0777);
    while (1) {

        fifo_fd = open(FIFO_PATH, O_RDONLY);
        if (fifo_fd < 0) { perror("error on opening FIFO for reading"); exit(1); }
        read(fifo_fd, &temp_data, sizeof(temp_data));
        close(fifo_fd);
        printf("Received data --> PID=%d, temperature=%d\n", temp_data.pid, temp_data.temperature);

        if (temp_data.temperature<min_temp) min_temp= temp_data.temperature;

        fifo_fd = open(FIFO_PATH, O_WRONLY);
        if (fifo_fd < 0) { perror("error on opening FIFO for writing"); exit(1); }
        write(fifo_fd, &min_temp, sizeof(min_temp));
        close(fifo_fd);

        printf("----------------------------------\n");
        printf("min temperature is = %d\n", min_temp);
        printf("----------------------------------\n");
    }

    unlink(FIFO_PATH);
    return 0;
}
