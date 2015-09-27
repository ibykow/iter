#ifndef ITER_H__
#define ITER_H__

#include "stdlib.h"

struct iter_info_s {
    void *arr, *ctx, (*iter)(void *, size_t, void *, size_t, void *);
    size_t size, len, i;
};

#define iter_info_init(p, a, c, it, s, l) *(p) = (struct iter_info_s) \
    { .arr = a, .ctx = c, .iter = it, .size = (size_t) s, .len = (size_t) l, .i = 0 }

#define iter_remaining(p) (p && (p)->arr && (p)->iter && (p)->size && \
    (p)->len && ((p)->i < (p)->len))

#define iter_next(infop) if (iter_remaining(infop)) iter_next_(infop)
#define iter_all(infop) while (iter_remaining(infop)) iter_next_(infop)

static inline void iter_next_(struct iter_info_s *info)
{
    info->iter(((char *) (info->arr)) + (info->i * info->size), info->i,
        info->arr, info->len, info->ctx);

    info->i++;
}

void for_each(void *arr, size_t size, size_t len, void *ctx,
    void (*iter)(void *, size_t, void *, size_t, void *));

#endif /* end of include guard: ITER_H__ */
