#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>


#define FREE1(obj) ({ assert(obj != NULL); free(obj); })
#define FREE2(obj1, obj2) ({ FREE1(obj1); FREE1(obj2); })
#define FREE3(obj, ...) ({ FREE1(obj); FREE2(__VA_ARGS__); })
#define FREE4(obj, ...) ({ FREE1(obj); FREE3(__VA_ARGS__); })
#define FREE5(obj, ...) ({ FREE1(obj); FREE4(__VA_ARGS__); })

#define GET_MACRO(_1, _2, _3, _4, _5, NAME, ...) NAME
#define FREE(...) GET_MACRO(__VA_ARGS__, FREE5, FREE4, FREE3, FREE2, FREE1)(__VA_ARGS__)


#define RETURN_IF_NULL(return_val, obj) ({ if (obj == NULL) return return_val; })

#define FREE_IF_NULL(return_val, obj, ...) ({ \
        if (obj == NULL) { \
            FREE(__VA_ARGS__); \
            return return_val; \
        } \
        })

#define MALLOC(return_val, obj, type, size) ({ \
        obj = (type *)malloc(sizeof(type) * (size)); \
        RETURN_IF_NULL(return_val, obj); \
        })

#define MALLOC_OR_FREES(return_val, obj, type, size, ...) ({ \
        obj = (type *)malloc(sizeof(type) * (size)); \
        FREE_IF_NULL(return_val, obj, __VA_ARGS__); \
        })
