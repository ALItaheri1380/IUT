#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define DEVICE_PATH "/dev/iut_audio_device"

int main() {
    int fd;
    char write_msg1[] = "Lorem ipsum dolor sit amet, consectetur**************";
    char write_msg2[] = "adipiscing elit, sed do eiusmod tempor************";
    char write_msg3[] = "incididunt ut labore et dolore magna aliqua.*****";
    char write_msg4[] = "Ut enim ad minim veniam, quis nostrud************";
    char write_msg5[] = "exercitation ullamco laboris nisi ut aliquip*****";

    char read_buffer[50];

    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device");
        return EXIT_FAILURE;
    }

    write(fd, write_msg1, strlen(write_msg1));
    printf("Written to device: %s\n", write_msg1);

    write(fd, write_msg2, strlen(write_msg2));
    printf("Written to device: %s\n", write_msg2);

    write(fd, write_msg3, strlen(write_msg3));
    printf("Written to device: %s\n", write_msg3);

    write(fd, write_msg4, strlen(write_msg4));
    printf("Written to device: %s\n", write_msg4);

    write(fd, write_msg5, strlen(write_msg5));
    printf("Written to device: %s\n", write_msg5);

    read(fd, read_buffer, sizeof(read_buffer));
    printf("Read from device: %s\n", read_buffer);

    close(fd);
    return EXIT_SUCCESS;
}
