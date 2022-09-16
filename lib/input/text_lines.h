#ifndef TEXT_LINES_H
#define TEXT_LINES_H

/**
 * @file text_lines.h
 * @author MeerkatBoss
 * @brief Contains function for reading lines from text file
 * @version 0.1
 * @date 2022-08-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>

/**
 * @brief 
 * Stores single text line with additional information
 */
typedef struct
{
    size_t line_number;
    size_t line_length;
    const char *line;
} Line;


/**
 * @brief 
 * Stores lines of a text file
 */
typedef struct
{
    const char *text;
    size_t text_len;
    Line *lines;
    size_t line_count;
} TextLines;

/**
 * @brief 
 * Skips non-alphanumeric characters in *`str`, moving pointer by
 * `step`. Ensures that the pointer is moved by less than `max_skip`
 * 
 * @param[inout] str - pointer to string
 * @param[in] max_skip - maximum allowed number of characters to skip
 * @param[in] step - movement step
 * @return Number of skipped characters
 */
size_t skip_not_alnum(const char **str, size_t max_skip, int step);

/**
 * @brief
 * Compares two strings with given length and step size
 * 
 * @param[in] str1 - first string
 * @param[in] str1_len - first string length
 * @param[in] str2 - second string
 * @param[in] str2_len - second string length
 * @param[in] step - movement step
 * @return Comparison result
 */
int compare_strings_with_steps(const char* str1, size_t str1_len,
                              const char* str2, size_t str2_len,
                              int step);

/**
 * @brief
 * Compares lines lexicographically,
 * ignoring whitespaces and punctuation
 * 
 * @param[in] a - first `Line`
 * @param[in] b - second `Line`
 * @return Comparison result
 */
int compare_lines(const void* a, const void* b);

/**
 * @brief
 * Compares lines lexicographically starting from line end,
 * ignoring whitespaces and punctuation
 * 
 * @param[in] a - first `Line`
 * @param[in] b - second `Line`
 * @return Comparison result
 */
int compare_lines_inverse(const void *a, const void *b);

/**
 * @brief Compares lines by their numbers
 * 
 * @param[in] a - first `Line`
 * @param[in] b - second `Line`
 * @return Comparison result
 */
int compare_lines_by_number(const void *a, const void *b);

/**
 * @brief Creates `TextLines` instance, reads specified file
 * 
 * @param[in] path - path to opened file
 * @return `TextLines` instance with stored file contents
 */
TextLines read_file(const char* path);

/**
 * @brief Frees lines contained within `TextLines` instance
 * 
 * @param[in] txlines - TextLines instance
 */
void dispose_lines(TextLines* txlines);

#endif