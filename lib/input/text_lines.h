#ifndef TEXT_LINES_H
#define TEXT_LINES_H

/**
 * @file text_lines.h
 * @author MeerkatBoss
 * @brief Work with files line by line
 * @version 0.1
 * @date 2022-08-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>

/**
 * @brief 
 * Single text line with additional information
 */
typedef struct
{
    size_t line_length;
    const char *line;
} Line;


/**
 * @brief 
 * Lines of a text file
 */
typedef struct
{
    const char *text;
    size_t text_len;
    Line *lines;
    size_t line_count;
} TextLines;

enum direction
{
    BACKWARD = -1,
    FORWARD  =  1
};

/**
 * @brief 
 * Skip non-alphanumeric characters in *`str`, moving pointer by
 * `step`. Ensure that the pointer is moved by less than `max_skip`
 * 
 * @param[in] str - string
 * @param[in] max_skip - maximum allowed number of characters to skip
 * @param[in] dir - movement direction
 * @return Number of skipped characters
 */
size_t skip_not_alnum(const char *str, size_t max_skip, enum direction dir);


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

/**
 * @brief Create `TextLines` instance, reads specified file
 * 
 * @param[in] path - path to opened file
 * @return `TextLines` instance with stored file contents
 */
TextLines read_file(const char* path);

/**
 * @brief Free lines contained within `TextLines` instance
 * 
 * @param[in] txlines - TextLines instance
 */
void dispose_lines(TextLines* txlines);

#endif
