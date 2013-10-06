#include "c_utils.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void _c_assert(const char* cond, const char* file, int line, int panic) {
    printf("assert '%s' failed @ (%s, %d)\n", cond, file, line);
    if (panic) {
        abort();
    }
}

void* _c_alloc(size_t size, const char* name, int line) {
    void *p = NULL;
    ASSERT(size != 0);

    p = malloc(size);
    if (!p) {
        /* TODO(dongxu) add logger output */
    }
    return p;
}
void* _c_zalloc(size_t size, const char* name, int line) {
    void *p = NULL;
    p = _c_alloc(size, name, line);
    if (p != NULL) {
        memset(p, 0, size);
    }
    return p;
}

void* _c_calloc(size_t nmemb, size_t size, const char* name, int line) {
    return _c_zalloc(nmemb * size, name, line);
}
void* _c_realloc(void* ptr, size_t size, const char* name, int line) {
    void *p = NULL;

    ASSERT(size != 0);

    p = realloc(ptr, size);
    if (p == NULL) {
        /* TODO(dongxu): add logger */
    }
    return p;
}

void* _c_free(void* ptr, const char* name, int line) {
    ASSERT(ptr != NULL);
    free(ptr);
}

