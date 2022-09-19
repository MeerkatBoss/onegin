#ifndef SORTING_H
#define SORTING_H

/**
 * @file sorting.h
 * @author MeerkatBoss
 * @brief Sorter functions
 * @version 0.1
 * @date 2022-09-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stddef.h>

/**
 * @brief 
 * Type alias for abstract comparator
 */
typedef int comparator_t(const void*, const void*);

/**
 * @brief 
 * Type alias for sorting function
 */
typedef void (*sorter_t)(void* arr, size_t arr_len,
                       size_t element_size, comparator_t* cmp);

/**
 * @brief
 * Default comparator for strings
 * 
 * @param[in] a - fisrt  string
 * @param[in] b - second string
 * @return Comparison result
 */
int compare_strings(const void *a, const void *b);

/**
 * @brief
 * Default comparator for integers
 * 
 * @param[in] a - fisrt  number
 * @param[in] b - second number
 * @return Comparison result
 */
int compare_int(const void *a, const void *b);

/**
 * @brief
 * Exchange given number of bytes between given
 * memory areas
 * 
 * @param[inout] a - address of the first  memory area
 * @param[inout] b - address of the second memory area
 * @param[in] size - number of bytes to exchange
 * @param[out] buf - intermediate swap buffer. If this
 * parameter is `NULL`, the buffer will be allocated
 * inside function
 * 
 * @warning 
 * If memory areas overlap the result is undefined
 */
void memswap(void* a, void* b, size_t size, void* buf);

/**
 * @brief 
 * Sort array using given comparator
 * with insertion sort algorithm.
 * 
 * @param[inout] arr - array to sort
 * @param[in] arr_len - number of elements in `arr`
 * @param[in] element_size - size (in bytes) of each array element
 * @param[in] cmp - comparison function
 */
void insertion_sort(void* arr, size_t arr_len,
                    size_t element_size, comparator_t* cmp);

/**
 * @brief 
 * Sort array using given comparator
 * with merge sort algorithm.
 * 
 * @param[inout] arr - array to sort
 * @param[in] arr_len - number of elements in `arr`
 * @param[in] element_size - size (in bytes) of each array element
 * @param[in] cmp - comparison function
 * 
 * @warning NOT IMPLEMENTED
 */
void merge_sort(void* arr, size_t arr_len,
                size_t element_size, comparator_t* cmp);   //TODO

/**
 * @brief 
 * Sort array using given comparator
 * with quick sort algorithm.
 * 
 * @param[inout] arr - array to sort
 * @param[in] arr_len - number of elements in `arr`
 * @param[in] element_size - size (in bytes) of each array element
 * @param[in] cmp - comparison function
 * 
 * @warning NOT IMPLEMENTED
 */
void quick_sort(void* arr, size_t arr_len,
                size_t element_size, comparator_t* cmp);   //TODO

#endif
