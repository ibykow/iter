#include "iter.h"

void for_each(void *arr, size_t size, size_t len, void *ctx,
    void (*iter)(void *, size_t, void *, size_t, void *))
{
    if (len < 1)
        return;

    if (len == 1) {
        iter(arr, 0, arr, len, ctx);
        return;
    }

    size_t i;
    char *data = (char *) arr;
    for (i = 0; i < len; i++)
        iter(data + (i * size), i, arr, len, ctx);
}
