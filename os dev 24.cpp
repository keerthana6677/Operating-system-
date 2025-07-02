#include <stdio.h>
#include <fcntl.h>     // For open()
#include <unistd.h>    // For read(), write(), close()
#include <string.h>    // For strlen()

int main() {
    int fd;
    char writeData[] = "Hello! This is a demo of UNIX file system calls.\n";
    char readData[100];

    // Open file for writing (create if doesn't exist), with read & write permission
    fd = open("demo.txt", O_CREAT | O_RDWR, 0666);
    if(fd < 0) {
        perror("File open failed");
        return 1;
    }

    // Write data to file
    write(fd, writeData, strlen(writeData));

    // Move file pointer to start
    lseek(fd, 0, SEEK_SET);

    // Read data from file
    int n = read(fd, readData, sizeof(readData)-1);
    if(n < 0) {
        perror("Read failed");
        close(fd);
        return 1;
    }

    // Null terminate the string and print
    readData[n] = '\0';
    printf("Data read from file:\n%s", readData);

    // Close file
    close(fd);

    return 0;
}
