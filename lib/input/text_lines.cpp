#include "text_lines.h"
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

/**
 * @brief Maps file lines to memory
 * 
 * @param[in] path - path to file
 * @param[out] file_size - pointer to file size
 * @return file contents
 */
static size_t map_file(const char *path, char **text)
{
    //TODO: indicate errors by `memset`ting `text`
    assert(path != NULL);

    /* Open file descriptor */
    int fd = open(path, O_RDONLY);
    if (fd < 0) {/* Cannot open file, errno set by open */
        perror("Cannot open file.");
        return 0;
    }

    /* Get file size */
    struct stat file_stat = {};
    if (fstat(fd, &file_stat) < 0) /* Cannot read file, errno set by fstat */
    {
        int tmp = errno;
        close(fd);
        errno = tmp;
        return 0;
    }

    /* Call mmap */
    char *mapping = (char*) mmap(
        NULL, (size_t)file_stat.st_size + 1u, /* Map extra byte for final '\0' */
        PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    close(fd);
    if (mapping == MAP_FAILED) /* Mapping failed, errno set by mmap */
    {
        perror("Failed to read file.");
        return 0;
    }

    *text = mapping;
    return (size_t)file_stat.st_size + 1u;
}

static size_t split_text(char *text, size_t text_len)
{
    size_t line_count = 1;
    for (size_t i = 0; i < text_len - 1; i++)
        if (text[i] == '\n')
        {
            text[i] = '\0';
            line_count++;
        }
    text[text_len - 1] = '\0';
    return line_count;
}

TextLines read_file(const char *path)
{
    char *text = NULL;
    size_t text_len = map_file(path, &text);

    if (text == NULL)
        return {.text = NULL,
                .text_len = 0,
                .lines = NULL,
                .line_count = 0};

    size_t line_count = split_text(text, text_len);

    Line *lines = (Line*) calloc(line_count, sizeof(*lines));
    char *last_line = text; /* Pointer to the beginning of last line */
    size_t line_num = 0;
    for (size_t i = 0; i < text_len; i++)
        if (text[i] == '\0') /* Line ended */
        {
            lines[line_num] = {
                .line_number = line_num,
                .line_length = (size_t)(&text[i] - last_line),
                .line = last_line
            };
            line_num++; /* Increment line number */
            last_line = &text[i + 1]; /* Next line begins on i+1st position */
        }

    return {
            .text = (const char*) text,
            .text_len = text_len,
            .lines = lines,
            .line_count = line_count
        };
}

void dispose_lines(TextLines *txlines)
{
    if (txlines == NULL || txlines->lines == NULL)
        return;

    munmap((char *)txlines->text, txlines->text_len);
    txlines->text = NULL;

    free((char **)txlines->lines);
    txlines->lines = NULL;
}

size_t skip_not_alnum(const char **str, size_t max_skip, int step)
{
    size_t abs_step = (size_t) (step >= 0 ? step : -step);
    size_t pos = 0;

    for(pos = 0; pos < max_skip; pos += abs_step)
    {
        if (isalnum(**str))
            break;;
        *str += step;
    }
    return pos;
}

int compare_strings_with_steps(const char* str1, size_t str1_len,
                               const char* str2, size_t str2_len,
                               int step)
{
    size_t abs_step = (size_t) (step >= 0 ? step : -step);
    size_t index1 = 0, index2 = 0;

    for(
        ;
        index1 < str1_len && index2 < str2_len;
        index1 += abs_step, index2 += abs_step, str1 += step, str2 += step
    )
    {
        size_t skip1 = skip_not_alnum(&str1, str1_len - index1, step);
        size_t skip2 = skip_not_alnum(&str2, str2_len - index2, step);
        index1 += skip1;
        index2 += skip2;

        long long remaining1 = (long long)str1_len - (long long)index1;
        long long remaining2 = (long long)str2_len - (long long)index2;

        
        if (remaining1 == 0 ||
            remaining2 == 0)
        {
            if (remaining1 == remaining2)
                return 0;
            
            return remaining1 == 0
                    ? -1
                    :  1;
        }

        int diff = tolower(*str1) - tolower(*str2);
        if (diff)
            return diff;
    }
    if (index1 >= str1_len ||
        index2 >= str2_len)
    {
        if (index1 >= str1_len &&
            index2 >= str2_len)
                return 0;
        
        return index1 >= str1_len
                ? -1
                :  1;
    }

    return 0;
}

int compare_lines(const void* a, const void* b)
{
    assert(a != NULL);
    assert(b != NULL);
    const Line *a_line = (const Line*) a;
    const Line *b_line = (const Line*) b;

    assert(a_line->line != NULL);
    assert(b_line->line != NULL);

    return compare_strings_with_steps(
        a_line->line, a_line->line_length,
        b_line->line, b_line->line_length,
        1
    );
}

int compare_lines_inverse(const void *a, const void *b)
{
    assert(a != NULL);
    assert(b != NULL);
    const Line *a_line = (const Line*) a;
    const Line *b_line = (const Line*) b;

    assert(a_line->line != NULL);
    assert(b_line->line != NULL);

    return compare_strings_with_steps(
        a_line->line + a_line->line_length - 1, a_line->line_length,
        b_line->line + b_line->line_length - 1, b_line->line_length,
        -1
    );
}

int compare_lines_by_number(const void *a, const void *b)
{
    assert(a != NULL);
    assert(b != NULL);
    const Line *a_line = (const Line*) a;
    const Line *b_line = (const Line*) b;

    if (a_line->line_number < b_line->line_number)
        return -1;
    else if (a_line->line_number > b_line->line_number)
        return 1;
    return 0;
}
