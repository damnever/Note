#include <stdio.h>
#include <sys/utsname.h>

/*
 * If `uname` has no optional arguments, just print system name.
 * But `uname -a`(man 1 uname) will show more information than
 * `struct utsname`.
 */

int
main()
{
    struct utsname utsn;

    if (uname(&utsn) < 0) {
        fprintf(stderr, "Invoke uname error\n");
        return -1;
    }

    printf("sysname: %s\n", utsn.sysname);
    printf("nodename: %s\n", utsn.nodename);
    printf("release: %s\n", utsn.release);
    printf("version: %s\n", utsn.version);
    printf("machine: %s\n", utsn.machine);

    return 0;
}
