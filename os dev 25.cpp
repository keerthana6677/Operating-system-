#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    int fd;
    char buf[100];
    struct stat fileStat;

    // 1. open() & write()
    fd = open("sample.txt", O_CREAT | O_RDWR, 0644);
    if(fd < 0) {
        perror("Open failed");
        return 1;
    }
    write(fd, "Hello, UNIX system calls demo!\n", 31);

    // 2. fcntl() to get file descriptor flags
    int flags = fcntl(fd, F_GETFL);
    printf("File descriptor flags: %d\n", flags);

    // 3. lseek() to move file pointer back to start
    lseek(fd, 0, SEEK_SET);

    // 4. read() to read data from file
    int n = read(fd, buf, sizeof(buf)-1);
    buf[n] = '\0';
    printf("Data read from file: %s", buf);

    // 5. stat() to get file metadata
    if(stat("sample.txt", &fileStat) == 0) {
        printf("\nFile Size: %ld bytes\n", fileStat.st_size);
        printf("File Permissions: %o\n", fileStat.st_mode & 0777);
    } else {
        perror("stat failed");
    }

    close(fd);

    // 6. opendir() & readdir() to list current directory files
    DIR *dir = opendir(".");
    struct dirent *entry;

    if(dir == NULL) {
        perror("opendir failed");
        return 1;
    }

    printf("\nContents of current directory:\n");
    while((entry = readdir(dir)) != NULL) {
        printf(" - %s\n", entry->d_name);
    }
    closedir(dir);

    return 0;
}
