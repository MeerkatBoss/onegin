#ifndef TEXT_LINES_H
#define TEXT_LINES_H

/**
 * @file io_utils.h
 * @author MeerkatBoss
 * @brief Contains helper functions for IO
 * @version 0.1
 * @date 2022-08-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>

/**
 * @brief Wraps FILE*, provides access to line-by-line
 * reading of a file. Counts lines automatically,
 * starting at 0
 */
typedef struct
{
    const char *text;
    size_t text_len;
    const char ** lines;
    size_t line_count;
} TextLines;

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