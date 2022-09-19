#ifndef COMPARATORS_H
#define COMPARATORS_H

#include <stddef.h>
#include "text_lines.h"

enum direction
{
    BACKWARD = -1,
    FORWARD  =  1
};

/**
 * @brief
 * Compare two strings with given length and direction
 * 
 * @param[in] str1 - first string
 * @param[in] str1_len - first string length
 * @param[in] str2 - second string
 * @param[in] str2_len - second string length
 * @param[in] dir - movement direction
 * @return Comparison result
 */
int bidirectional_compare_strings(const char* str1, size_t str1_len,
                              const char* str2, size_t str2_len,
                              enum direction dir);

/**
 * @brief
 * Compare lines lexicographically,
 * ignoring whitespaces and punctuation
 * 
 * @param[in] a - first `Line`
 * @param[in] b - second `Line`
 * @return Comparison result
 */
int compare_lines(const void* a, const void* b);

/**
 * @brief
 * Compare lines lexicographically starting from line end,
 * ignoring whitespaces and punctuation
 * 
 * @param[in] a - first `Line`
 * @param[in] b - second `Line`
 * @return Comparison result
 */
int compare_lines_inverse(const void *a, const void *b);

/**
 * @brief Compare lines by their numbers
 * 
 * @param[in] a - first `Line`
 * @param[in] b - second `Line`
 * @return Comparison result
 */
int compare_lines_by_address(const void *a, const void *b);


#endif