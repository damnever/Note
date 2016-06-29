#ifndef __DBG_H__
#define __DBG_H__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG
#define debug(FMT, ...)
#else
#define debug(FMT, ...) fprintf(stderr, "DEBUG %s:%s:%d: " FMT "\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)
#endif

#define str_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(FMT, ...) fprintf(stderr, "[ERROR] (%s:%s:%d errno: %s) " FMT "\n", __FILE__, __func__, __LINE__, str_errno(), ##__VA_ARGS__)
#define log_warn(FMT, ...) fprintf(stderr, "[WARN] (%s:%s:%d errno: %s) " FMT "\n", __FILE__, __func__, __LINE__, str_errno(), ##__VA_ARGS__)
#define log_info(FMT, ...) fprintf(stderr, "[INFO] (%s:%s:%d) " FMT "\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#endif
