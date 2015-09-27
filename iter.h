#ifndef ITER_H__
#define ITER_H__

/*
 * iter.h
 * Ilia Bykow, 2015
 * Please contact for license.
 *
 * Iterate over arrays all at once or piecewise.
 *
 * Interface: for_each, iter_next, iter_all
 */

#include "stdlib.h"

/*
 * struct iter_info_s
 * This is a structure used by iter_next and iter_all.
 * Members:
 * arr, the array you wish to iterate over
 * ctx, a void pointer to any context data you want to provide to each iteration
 * iter, the function to call on each iteration (see below for parameter details)
 * size, the size of the array's members
 * len, the number of elements in the array
 *
 * iter (function) prototype:
 * void my_iter_function(void *current_element, size_t current_index,
 *      void *my_array, size_t len, void *ctx);
 *
 * current_element, a void pointer to the current array element
 * current_index, the index at which the current_element is located
 * my_array, the array you are iterating over
 * len, the number of elements in the array
 * ctx, a pointer to the context data provided by you
 */
struct iter_info_s {
    void *arr, *ctx, (*iter)(void *, size_t, void *, size_t, void *);
    size_t size, len, i;
};

#define iter_info_init(p, a, c, it, s, l) *(p) = (struct iter_info_s) \
    { .arr = a, .ctx = c, .iter = it, .size = (size_t) s, .len = (size_t) l, .i = 0 }

#define iter_remaining(p) (p && (p)->arr && (p)->iter && (p)->size && \
    (p)->len && ((p)->i < (p)->len))

/*
 * iter_next(infop)
 * Execute the current iteration as described by infop.
 * If no iterations remain, do nothing.
 *
 * infop, a pointer to an iter_info_s structure
 */
#define iter_next(infop) if (iter_remaining(infop)) iter_next_(infop)

/*
 * iter_all(infop)
 * Execute every remaining iteration as described by infop.
 * If/when no iterations remain, do nothing / stop.
 *
 * infop, a pointer to an iter_info_s structure.
 */
#define iter_all(infop) while (iter_remaining(infop)) iter_next_(infop)

static inline void iter_next_(struct iter_info_s *info)
{
    info->iter(((char *) (info->arr)) + (info->i * info->size), info->i,
        info->arr, info->len, info->ctx);

    info->i++;
}

/*
 * void for_each(void *arr, size_t size, size_t len, void *ctx,
 *      void (*iter)(void *, size_t, void *, size_t, void *))
 * Iterate over each element of the array from start to finish.
 * Call the function iter on each iteration.
 *
 * arr, the array to iterate over
 * size, the size of each element
 * len, the number of elements in the array
 * ctx, a pointer to any context data you may want to provide
 * iter, the function to call on every iteration (see description under the
 *      iter_info_s comment)
 */
void for_each(void *arr, size_t size, size_t len, void *ctx,
    void (*iter)(void *, size_t, void *, size_t, void *));

#endif /* end of include guard: ITER_H__ */
