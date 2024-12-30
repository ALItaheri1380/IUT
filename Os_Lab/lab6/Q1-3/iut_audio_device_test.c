#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "utils.h"   

#define DEVICE_PATH "/dev/iut_audio_device"

int main() {
    int fd, ret;

    struct headset_data *data = malloc(sizeof(struct headset_data));
    memset(data, 0, sizeof(struct headset_data));

    char write_msg1[] = "Alles hat ein Ende, nur die Wurst hat zwei."; 
    char write_msg2[] = "Ubung macht den Meister."; 

    char read_buffer[50];
    
    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device");
        return EXIT_FAILURE;
    }

    printf("Read 1\n");
    read(fd, read_buffer, sizeof(read_buffer));
    printf("Read from device: %s\n", read_buffer);

    ret = ioctl(fd, Mute , data);
    if (ret < 0) {
        perror("ioctl");
        exit(0);
    }
    printf("Mute\n");


    printf("Read 2\n");
    ret = read(fd, read_buffer, sizeof(read_buffer));

    if(ret < 0)
        printf("Read failed.\n");

    ret = ioctl(fd, Unmute , data);
    if (ret < 0) {
        perror("ioctl");
        exit(0);
    }
    printf("Unmute\n");

    printf("Read 3\n");
    read(fd, read_buffer, sizeof(read_buffer));
    printf("Read from device: %s\n", read_buffer);

    printf("--------------------------------\n");
    printf("--------------------------------\n");
    printf("--------------------------------\n");
    printf("--------------------------------\n");


    printf("Write 1\n");
    write(fd, write_msg1, strlen(write_msg1));
    printf("--------------------------------\n");

    data->volume = 0;
    ret = ioctl(fd, setVolume , data);
    if (ret < 0) {
        perror("ioctl");
        exit(0);
    }
    printf("Set volume to %d\nresult: %s\n", data->volume, data->message);

    printf("--------------------------------\n");
    
    printf("Write 2\n");
    write(fd, write_msg2, strlen(write_msg2));

    data->volume = 50;
    ret = ioctl(fd, setVolume , data);
    if (ret < 0) {
        perror("ioctl");
        exit(0);
    }
    printf("Set volume to %d\nresult: %s\n", data->volume, data->message);

    ret = ioctl(fd, getVolume , data);
    if (ret < 0) {
        perror("ioctl");
        exit(0);
    }
    printf("Get volume: %d\nresult: %s\n", data->volume, data->message);
    printf("--------------------------------\n");
    
    printf("Write 3\n");
    write(fd, write_msg2, strlen(write_msg2));

    printf("--------------------------------\n");

    data->volume = -5;
    ret = ioctl(fd, setVolume , data);
    if (ret < 0) {
        perror("ioctl");
        exit(0);
    }
    printf("Set volume to %d\nresult: %s\n", data->volume, data->message);
    printf("--------------------------------\n");

    close(fd);
    return EXIT_SUCCESS;
}

