#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/* Can read but can not write,
 * because O_APPEND always move file pointer to file tail when you write.
 * Use `od -c test.txt` to see file content.
 */

int
main()
{
    int fd;
    char buffer[] = "abcdefghijklmnopqrst";
    char buf[8];
    char buf2[4] = "DXC";

    if((fd = open("./test.txt", O_RDWR | O_CREAT | O_APPEND)) < 0) {
        fprintf(stderr, "Open or create test.txt error\n");
        exit(1);
    }

    if(write(fd, buffer, 21) != 21) {
        fprintf(stderr, "write error\n");
        exit(1);
    }

    if(-1 == lseek(fd, 7, SEEK_SET)) {
        fprintf(stderr, "lseek error\n");
        exit(1);
    }

    if(-1 == read(fd, buf, 8)) {
        fprintf(stderr, "read error\n");
        exit(1);
    }
    buf[7] = 0;
    printf("READ: %s\n", buf);  /* hijklmn */

    if(-1 == lseek(fd, 7, SEEK_SET)) {
        fprintf(stderr, "lseek error\n");
        exit(1);
    }

    if(write(fd, buf2, 4) != 4) {
        fprintf(stderr, "write error\n");
        exit(1);
    }

    if(-1 == lseek(fd, 7, SEEK_SET)) {
        fprintf(stderr, "lseek error\n");
        exit(1);
    }

    buf[0] = 0;
    if(-1 == read(fd, buf, 4)) {
        fprintf(stderr, "read error\n");
        exit(1);
    }

    buf[3] = 0;
    printf("READ: %s\n", buf);  /* hij */

    buf[0] = 0;
    if(-1 == lseek(fd, -4, SEEK_END)) {
        fprintf(stderr, "lseek error\n");
        exit(1);
    }

    buf[0] = 0;
    if(-1 == read(fd, buf, 4)) {
        fprintf(stderr, "read error\n");
        exit(1);
    }

    buf[3] = 0;
    printf("READ: %s\n", buf);  /* DXC */

    return 0;
}
