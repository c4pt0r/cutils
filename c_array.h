#ifndef C_ARRAY_H_
#define C_ARRAY_H_
#include <stdint.h>
#include <stddef.h>
typedef int (*c_array_compare_t)(const void*, const void*);
typedef void (*c_array_each_t)(void*, void*);

struct c_array {
    uint32_t nelem;
    void*    elem;
    size_t   esize;
    uint32_t nalloc;
};

#define NULL_C_ARRAY {0, NULL, 0, 0}

static inline void c_array_null(struct c_array* a) {
    a->nelem = 0;
    a->elem = NULL;
    a->esize = 0;
    a->nalloc = 0;
}

static inline void c_array_set(struct c_array* a, void* elem, size_t sz, uint32_t nalloc) {
    a->nelem = 0;
    a->elem = elem;
    a->esize = sz;
    a->nalloc = nalloc;
}

static inline uint32_t c_array_size(const struct c_array* a) {
    return a->nelem;
}

/* n means array size, sz means element size */
struct c_array* c_array_create(uint32_t n, size_t sz);
void c_array_destroy(struct c_array* a);

int c_array_init(struct c_array* a, uint32_t n, size_t sz);
void c_array_uninit(struct c_array* a);

uint32_t c_array_index(struct c_array* a, void* elem);
void* c_array_push(struct c_array* a);
void* c_array_pop(struct c_array* a);
void* c_array_get(struct c_array* a);
void* c_array_top(struct c_array* a);
void c_array_sort(struct c_array* a, c_array_compare_t comp_func);
void c_array_each(struct c_array* a, c_array_each_t, void *data);

#endif
