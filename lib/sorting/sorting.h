#ifndef SORTING_H
#define SORTING_H

#include <stddef.h>

typedef int (*comparator)(void*, void*);

typedef void (*sorter)(void*, void*, size_t, comparator);


#define COMPARATOR(name) compare_##name
#define DECLARE_COMPARATOR(name) int COMPARATOR(name)(void* a, void* b)

DECLARE_COMPARATOR(char);
DECLARE_COMPARATOR(schar);
DECLARE_COMPARATOR(short);
DECLARE_COMPARATOR(ushort);
DECLARE_COMPARATOR(int);
DECLARE_COMPARATOR(uint);
DECLARE_COMPARATOR(long);
DECLARE_COMPARATOR(ulong);
DECLARE_COMPARATOR(llong);
DECLARE_COMPARATOR(ullong);
DECLARE_COMPARATOR(string);

#undef DECLARE_COMPARATOR


void insertion_sort(void* start, void* end,
                    size_t element_size, comparator cmp);

void merge_sort(void* start, void* end,
                size_t element_size, comparator cmp);

void quick_sort(void* start, void* end,
                size_t element_size, comparator cmp);

#endif