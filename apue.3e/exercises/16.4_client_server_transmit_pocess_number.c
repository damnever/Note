#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <getopt.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/*
 * Server send process number, client receives it and print.
 *
 * Usage:
 *   SERVER:
 *       ./program --server [--host 127.0.0.1] [--port 8080]
 *   CLIENT:
 *       ./program --client [--host 127.0.0.1] [--port 8080]
 */
#define BUFFER_SIZE 512
#define BACKLOG 5

static int server = false;
static int client = false;
static const char *host = "127.0.0.1";
static int port = 8080;

static void parse_options(int argc, char *argv[]);
static void print_help(char *name);
static void run_server();
static void serve(int sockfd);
static void run_client();
static int set_cloexec(int fd);


int
main(int argc, char *argv[])
{
    int failed = false;

    parse_options(argc, argv);

    if (server && client) {
        fprintf(stderr, "The program can not be server and client at the same time!\n");
        failed = true;
    } else if (!server && !client) {
        fprintf(stderr, "Argument `-s/--server` or `-c/--client` is required.\n");
        failed = true;
    }
    if (failed) {
        print_help(argv[0]);
        abort();
    }

    if (server) {
        run_server();
    } else if (client) {
        run_client();
    }

    return 0;
}


static void
parse_options(int argc, char *argv[])
{
    int next_option;

    static struct option long_options[] = {
        {"server", no_argument, NULL, 's'},
        {"client", no_argument, NULL, 'c'},
        {"host", required_argument, NULL, 'h'},
        {"port", required_argument, NULL, 'p'},
        {NULL, 0, NULL, 0}
    };

    while ((next_option = getopt_long(argc, argv, "sch:p:", long_options, NULL)) != -1) {
        switch (next_option) {
            case 's':
                server = true;
                break;
            case 'c':
                client = true;
                break;
            case 'h':
                host = optarg;
                break;
            case 'p':
                port = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Unknown argument: %c(%s)\n", next_option, optarg);
                print_help(argv[0]);
                exit(1);
        }
    }
}

static void
print_help(char *name)
{
    fprintf(stderr, "Usage: %s --server/client [--host HOST] [--port PORT]\n\n", name);
    fprintf(stderr, "required arguments:\n"
            "  -s --server     run program as server side\n"
            "  -c --client     run program as client side\n"
            "optional arguments:"
            "  -h --host HOST  server address, default to %s\n"
            "  -p --port PORT  port to listen, default to %d\n",
            host, port);
}

/* Server */
static void
run_server()
{
    int sockfd;
    struct sockaddr_in addr;
    char yes = '1';

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(host);
    memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));

    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    setsockopt(sockfd, SOL_SOCKET,SO_REUSEADDR, &yes, sizeof(int));
    bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    listen(sockfd, BACKLOG);
    serve(sockfd);
}

static void
serve(int sockfd)
{
    int client_fd;
    FILE *fp;
    char buf[BUFFER_SIZE];

    set_cloexec(sockfd);
    for (;;) {
        if ((client_fd = accept(sockfd, NULL, NULL)) < 0) {
            fprintf(stderr, "accept() got error: %s\n", strerror(errno));
            exit(1);
        }
        set_cloexec(client_fd);
        if ((fp = popen("/bin/ps -A | /usr/bin/wc -l", "r")) == NULL) {
            sprintf(buf, "Error: %s\n", strerror(errno));
        } else {
            fgets(buf, BUFFER_SIZE, fp);
            pclose(fp);
        }
        fprintf(stdout, "Got a client connection!\n");
        send(client_fd, buf, strlen(buf), 0);
        close(client_fd);
    }
}


/* Client */
static void
run_client()
{
    int sockfd, size;
    struct sockaddr_in addr;
    char buf[BUFFER_SIZE];

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(host);
    memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));

    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));

    size = recv(sockfd, buf, BUFFER_SIZE, 0);
    buf[size + 1] = '\0';
    printf("Server process number: %s\n", buf);
}

static int
set_cloexec(int fd)
{
    int val;

    if ((val = fcntl(fd, F_GETFD, 0)) < 0) {
        return -1;
    }
    val |= FD_CLOEXEC;
    return fcntl(fd, F_SETFD, val);
}
