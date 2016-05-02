#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>


void print_size(int fd, int optname, char *name);


int
main()
{
    int tcp, udp;

    if ((tcp = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        exit(1);
    }
    if ((udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        exit(1);
    }

    print_size(tcp, SO_SNDBUF, "TCP SEND BUFFER");
    print_size(tcp, SO_RCVBUF, "TCP RECV BUFFER");
    print_size(udp, SO_SNDBUF, "UDP SEND BUFFER");
    print_size(udp, SO_RCVBUF, "UDP RECV BUFFER");

    close(tcp);
    close(udp);

    return 0;
}

void
print_size(int fd, int optname, char *name)
{
    int size;
    socklen_t len;

    if (getsockopt(fd, SOL_SOCKET, optname, &size, &len) < 0) {
        exit(1);
    }

    // use SO_TYPE?
    printf("%s: %d\n", name, size);
}
