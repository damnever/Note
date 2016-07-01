#include <stdio.h>
#include <apr_general.h>
#include <apr_getopt.h>
#include <apr_strings.h>
#include <apr_lib.h>

#include "dbg.h"
#include "cmds.h"
#include "db.h"



static void print_help();


int main(int argc, const char * const argv[])
{
    apr_pool_t *p = NULL;
    apr_pool_initialize();
    apr_pool_create(&p, NULL);

    apr_getopt_t *opt;
    apr_status_t rv;

    char ch = '\0';
    const char *optarg = NULL;
    const char *config_opts = NULL;
    const char *make_opts = NULL;
    const char *install_opts = NULL;
    const char *url = NULL;
    enum CommandType request = COMMAND_NONE;

    rv = apr_getopt_init(&opt, p, argc, argv);

    while (apr_getopt(opt, "I:Lc:m:i:d:SF:B:h:", &ch, &optarg) == APR_SUCCESS) {
        switch (ch) {
            case 'I':
                request = COMMAND_INSTALL;
                url = optarg;
                break;
            case 'L':
                request = COMMAND_LIST;
                break;
            case 'c':
                config_opts = optarg;
                break;
            case 'm':
                make_opts = optarg;
                break;
            case 'i':
                install_opts = optarg;
                break;
            case 'S':
                request = COMMAND_INIT;
                break;
            case 'F':
                request = COMMAND_FETCH;
                url = optarg;
                break;
            case 'B':
                request = COMMAND_BUILD;
                url = optarg;
                break;
            case 'h':
                break;
        }
    }

    switch (request) {
        case COMMAND_INSTALL:
            check(url, "You must at least give an URL.");
            Command_install(p, url, config_opts, make_opts, install_opts);
            break;
        case COMMAND_LIST:
            DB_list();
            break;
        case COMMAND_FETCH:
            check(url, "You must give an URL.");
            Command_fetch(p, url, 1);
            log_info("Downloaded to %s and in /tmp/", BUILD_DIR);
            break;
        case COMMAND_BUILD:
            check(url, "You must give an URL.");
            Command_build(p, url, config_opts, make_opts, install_opts);
            break;
        case COMMAND_INIT:
            rv = DB_init();
            check(rv == 0, "Failed to make the database.");
            break;
        default:
            sentinel("Invalid command given.");
    }

    return 0;

error:
    print_help();
    return 1;
}

static void print_help()
{
    printf("Usage: devpkg -I|F|B|S URL -c|m|i OPTIONS.\n");
    printf(" -h               Print this message and exit.\n");
    printf(" -I URL           Install package from URL.\n");
    printf(" -L               List all installed packages.\n");
    printf(" -c config_opts   Specify configure options.\n");
    printf(" -m make_opts     Specify build options.\n");
    printf(" -i install_opts  Specify install options.\n");
    printf(" -S               Initialize database.\n");
    printf(" -F URL           Only download package from URL.\n");
    printf(" -B URL           Build package from URL.");
}
