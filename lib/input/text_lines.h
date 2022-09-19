#ifndef TEXT_LINES_H
#define TEXT_LINES_H

// TODO: No reason to write "Contains functions ...", it's obvious
//       to any developer reading your code, just clutters documentation.
//       (applies to pretty much all the documentation, do not describe
//        nature of the entity you're documenting, it's usually well-know,
//        obvious or unimportant. Explain it's purpose and function)
//
//       In general, it's advised by many to write documentation in imperative.
//
//       For example, instead of:
//           Function that reads file and puts...
//
//       You could write:
//           Read file and put...
//
//       Note absence of "s" after verbs, it's because we are no longer
//       describing function in third person, we're just telling user
//       what's gonna happen when he calls it!
//
//       This "s" absence is common for all imperative sentences.
//       And, I general, is consider a good style, which make documentation
//       less wishy-washy and more straight-to-the-point.
//
//       Note: I think, I general, you did a great job writing documentation
//             for this project, I partially copied this message from 
//             other review, because I thought it could give you some insightful
//             points too, especially about writing in imperative.
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

enum direction
{
    BACKWARD = -1,
    FORWARD  =  1
};

/**
 * @brief 
 * Skips non-alphanumeric characters in *`str`, moving pointer by
 * `step`. Ensures that the pointer is moved by less than `max_skip`
 * 
 * @param[in] str - string
 * @param[in] max_skip - maximum allowed number of characters to skip
 * @param[in] dir - movement direction
 * @return Number of skipped characters
 */
size_t skip_not_alnum(const char *str, size_t max_skip, enum direction dir);


/**
 * @brief
 * Compares two strings with given length and direction
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
int compare_lines_by_address(const void *a, const void *b);

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
