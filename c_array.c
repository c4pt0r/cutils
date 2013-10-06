#include "c_array.h"
#include "c_utils.h"

#include <stdlib.h>

struct c_array* c_array_create(uint32_t n, size_t sz) {
    struct c_array* a;
    a = c_alloc(sizeof(*a));
    if (a == NULL) {
        return NULL;
    }
    a->elem = c_alloc(n * sz);

    if (a->elem == NULL) {
        c_free(a);
        return NULL;
    }

    a->nelem = 0;
    a->esize = sz;
    a->nalloc = n;
}

void c_array_destroy(struct c_array* a) {
    c_array_uninit(a);
    c_free(a);
}

int c_array_init(struct c_array* a, uint32_t n, size_t sz) {
    a->elem = c_alloc(n*sz);
    if (a->elem == NULL) {
        return -1;
    }

    a->nelem = 0;
    a->esize = sz;
    a->nelem = n;
    return 0;
}

void c_array_uninit(struct c_array* a) {
    if (a->elem != NULL) {
        c_free(a->elem);
    }
}

uint32_t c_array_index(struct c_array* a, void* elem) {
    void *p, *q;
    uint32_t off, index;
    ASSERT(a && elem && elem > a);

    p = a->elem;
    q = elem;

    off = (uint32_t)(q - p);
    ASSERT(off % (uint32_t)(a->esize) == 0);

    index = off / (uint32_t)(a->esize);
    return index;
}

void* c_array_push(struct c_array* a) {
    void* elem, *new;
    size_t size;
    if (a->nelem == a->nalloc) {
        /* expand */
        /* calc total size */
        size = a->esize * a->nalloc;
        new = c_realloc(a->elem, 2 * size);
        if (new == NULL) {
            return NULL;
        }
        a->elem = new;
        a->nalloc *= 2;
    }
    /* move to tail */
    elem = (void*)a->elem + a->esize * a->nelem;
    a->nelem++;
    return elem;
}

void* array_pop(struct c_array* a) {
    void* elem;
    ASSERT(a->nelem != 0);

    a->nelem--;
    elem = a->elem + a->esize * a->nelem;

    return elem;
}

void* c_array_get(struct c_array* a, uint32_t idx) {
    ASSERT(a->nelem != 0 && idx < a->nelem);
    return a->elem + (a->esize * idx);
}

void* c_array_top(struct c_array* a) {
    return c_array_get(a, a->nelem - 1);
}

void c_array_sort(struct c_array* a, c_array_compare_t comp_func) {
    qsort(a->elem, a->nelem, a->esize, comp_func);
}

void c_array_each(struct c_array* a, c_array_each_t func, void* data) {
    uint32_t i;
    for (i = 0 ; i < c_array_size(a); i++) {
        void *elem = c_array_get(a, i);
        ASSERT(elem);
        func(elem, data);
    }
}
