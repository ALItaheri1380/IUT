#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define DEVICE_PATH "/dev/iut_audio_device"

int main() {
    int fd;
    char write_msg1[] = "Alles hat ein Ende, nur die Wurst hat zwei."; 
    char write_msg2[] = "Ubung macht den Meister."; 

    char read_buffer[50];
    
    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device");
        return EXIT_FAILURE;
    }

    write(fd, write_msg1, strlen(write_msg1));

    write(fd, write_msg2, strlen(write_msg2));

    read(fd, read_buffer, sizeof(read_buffer));
    printf("Read from device: %s\n", read_buffer);

    read(fd, read_buffer, sizeof(read_buffer));
    printf("Read from device: %s\n", read_buffer);

    close(fd);
    return EXIT_SUCCESS;
}
