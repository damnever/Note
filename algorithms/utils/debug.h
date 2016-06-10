#ifndef _TEST_H_
#define _TEST_H_

#include <stdio.h>
#include <stdlib.h>

#define DEBUG(format, args...)                          \
    do {                                                \
        fprintf(stderr, "DEBUG: %s:%d:%s(): "#format,   \
                __FILE__, __LINE__, __func__,  ##args); \
    } while (0);

#endif
