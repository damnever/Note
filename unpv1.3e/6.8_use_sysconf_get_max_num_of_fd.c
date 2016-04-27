/*
 * http://man7.org/linux/man-pages/man3/sysconf.3.html
 * $ limit
 */

#include <stdio.h>
#include <unistd.h>
#include <limits.h>


int main()
{
    printf("_SC_OPEN_MAX=%ld\n", sysconf(_SC_OPEN_MAX));
    printf("OPEN_MAX=%d\n", OPEN_MAX);

    return 0;
}
