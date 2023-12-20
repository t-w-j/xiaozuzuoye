#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // 创建有名管道
    if (mkfifo("/tmp/myfifo", 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // 打开有名管道进行写操作
    int write_fd = open("/tmp/myfifo", O_WRONLY);
    assert(write_fd >= 0);
    char buffer[20];
    sprintf(buffer, "Hello from the write end!\n");
    int write_rc = write(write_fd, buffer, strlen(buffer));
    assert(write_rc == (strlen(buffer)));
    close(write_fd);

    // 打开有名管道进行读操作
    int read_fd = open("/tmp/myfifo", O_RDONLY);
    assert(read_fd >= 0);
    char read_buffer[20];
    int read_rc = read(read_fd, read_buffer, sizeof(read_buffer) - 1);
    assert(read_rc > 0);
    read_buffer[read_rc] = '\0';
    printf("Read from the read end: %s\n", read_buffer);
    close(read_fd);

    return 0;
}
