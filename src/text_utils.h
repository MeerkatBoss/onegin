#ifndef TEXT_UTILS_H
#define TEXT_UTILS_H

/**
 * @file text_utils.h
 * @author MeerkatBoss
 * @brief Contains utility input/output fucntions
 * @version 0.1
 * @date 2022-09-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "text_lines.h"
#include <stdio.h>

/**
 * @brief Outputs `Line` array
 * 
 * @param[in] lines - array to print
 * @param[in] line_count - number of elements in `lines`
 * @param[inout] stream - output stream
 */
void print_lines(const Line *lines, size_t line_count, FILE *stream);

#endif