#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/*
 * Create a hole in file.
 * Use `od -c file` to see file content.
 */

int
main(int argc, char *argv[])
{
    int fd;

    if(2 != argc) {
        printf("Usage: ./program filename\n");
        return 1;
    }

    if((fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666)) < 0) {
        fprintf(stderr, "create file %s error\n", argv[1]);
        return 1;
    }

    if(write(fd, "test", 5) != 5) {
        fprintf(stderr, "write to file %s error\n", argv[1]);
        return 1;
    }

    if(lseek(fd, 1000, SEEK_SET) < 0) {
        fprintf(stderr, "lseek error\n");
        return 1;
    }

    if(write(fd, "content", 8) != 8) {
        fprintf(stderr, "write to file %s error\n", argv[1]);
        return 1;
    }

    // ...
    if(close(fd) < 0) {
        fprintf(stderr, "close fd %d error\n", fd);
        return 1;
    }

    return 0;
}
