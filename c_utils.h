#ifndef C_UTILS_H_
#define C_UTILS_H_
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
/*
 * Memory allaction and free wrapper
 * helper for tracing bugs
 */

#define ASSERT(_x) do { \
    if (!(_x)) _c_assert(#_x, __FILE__, __LINE__, 1); \
}while (0)

#define c_alloc(_s) \
    _c_alloc((size_t)(_s), __FILE__, __LINE__)

#define c_zalloc(_s) \
    _c_zalloc((size_t)(_s), __FILE__, __LINE__)

#define c_calloc(_n, _s) \
    _c_calloc((size_t)(_n), (size_t)(_s), __FILE__, __LINE__)

#define c_realloc(_p, _s) \
    _c_realloc(_p, (size_t)(_s), __FILE__, __LINE__)

#define c_free(_p) do { \
    _c_free(_p, __FILE__, __LINE__); \
    (_p) = NULL; \
} while (0)

void  _c_assert(const char* cond, const char* file, int line, int panic);
void* _c_alloc(size_t size, const char* name, int line);
void* _c_zalloc(size_t size, const char* name, int line);
void* _c_calloc(size_t nmemb, size_t size, const char* name, int line);
void* _c_realloc(void* ptr, size_t size, const char* name, int line);
void* _c_free(void* ptr, const char* name, int line);

#endif
