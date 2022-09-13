#include "sorting.h"
#include <string.h>
#include <stdlib.h>

int compare_strings(const void* a, const void* b)
{
    return strcmp(*(const char**)a, *(const char**)b);
}

int compare_int(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

void memswap(void *a, void *b, size_t size)
{
    void *tmp = calloc(1, size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
}

void insertion_sort(void *start, void *end,
                    size_t element_size, comparator cmp)
{
    for (char *i = (char*) start; i < end; i += element_size)
        for(char *j = i - element_size; j >= start; j -= element_size)
            if (cmp(j, j + element_size) > 0)
                memswap(j, j + element_size, element_size);
}