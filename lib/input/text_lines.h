#ifndef TEXT_LINES_H
#define TEXT_LINES_H

/**
 * @file text_lines.h
 * @author MeerkatBoss
 * @brief Contains helper functions for IO
 * @version 0.1
 * @date 2022-08-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>

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
 * @brief Creates TextLines, reads specified file
 * 
 * @param[in] path - path to opened file
 * @return Allocated TextLines with opened file 
 */
const TextLines read_file(const char* path);

/**
 * @brief Frees allocated TextLines and closes associated file
 * 
 * @param[in] txlines - TextLines instance
 */
void close_reader(const TextLines* txlines);

#endif