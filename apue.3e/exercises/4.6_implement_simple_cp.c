#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

/*
 * Implement a program like cp(1).
 * If src file has a hole, do not write 0 to des file.
 * Use ./create_hole_in_file.c to generate a hole in file...
 */


int
my_cp(char *src, char *des)
{
    int fd_src, fd_des, n;
    struct stat st_buf;
    char buffer;

    if((fd_src = open(src, O_RDONLY)) < 0) {
        fprintf(stderr, "open file %s error\n", src);
        return -1;
    }

    if(fstat(fd_src, &st_buf) != 0) {
        fprintf(stderr, "fstat fd %d error\n", fd_src);
        return -1;
    }

    if((fd_des = open(des, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, st_buf.st_mode)) < 0) {
        fprintf(stderr, "open file %s error\n", des);
        return -1;
    }

    while((n = read(fd_src, &buffer, 1)) > 0) {
        if('\0' == buffer) {
            continue;
        }
        if(write(fd_des, &buffer, n) != n) {
            fprintf(stderr, "wirte to file %s error\n", des);
            return -1;
        }
    }
    if(0 != n) {
        fprintf(stderr, "read from file %s error\n", src);
        return -1;
    }
    return 0;
}

int
main(int argc, char *argv[])
{
    if(3 != argc) {
        printf("Usage: ./program src_file des_file\n");
        exit(1);
    }

    my_cp(argv[1], argv[2]);

    return 0;
}
