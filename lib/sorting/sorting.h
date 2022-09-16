#ifndef SORTING_H
#define SORTING_H

#include <stddef.h>

typedef int (*comparator)(const void*, const void*);

typedef void (*sorter)(void* arr, size_t arr_len,
                       size_t element_size, comparator cmp);

int compare_strings(const void *a, const void *b);

int compare_int(const void *a, const void *b);

void memswap(void* a, void* b, size_t size);

void insertion_sort(void* arr, size_t arr_len,
                    size_t element_size, comparator cmp);

void merge_sort(void* arr, size_t arr_len,
                size_t element_size, comparator cmp);

void quick_sort(void* arr, size_t arr_len,
                size_t element_size, comparator cmp);

#endif