#include "sorting.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int compare_strings(const void* a, const void* b)
{
    assert(a != NULL);
    assert(b != NULL);

    return strcmp(*(const char* const*)a, *(const char* const*)b);
}

int compare_int(const void* a, const void* b)
{
    assert(a != NULL);
    assert(b != NULL);

    return *(const int*)a - *(const int*)b;
}

void memswap(void *a, void *b, size_t size)
{
    assert(a != NULL);
    assert(b != NULL);

    void *tmp = calloc(1, size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
}

void insertion_sort(void *arr, size_t arr_len,
                    size_t element_size, comparator_t* cmp)
{
    assert(arr != NULL);
    assert(cmp != NULL);

    char* start = (char*) arr;
    char* end = start + arr_len*element_size;
    for (char *i = start; i < end; i += element_size)
        for(char *j = i - element_size; j >= start; j -= element_size)
            if (cmp(j, j + element_size) > 0)
                memswap(j, j + element_size, element_size);
}