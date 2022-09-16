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

const TextLines read_file(const char *path)
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

void close_reader(const TextLines *txlines)
{
    if (txlines == NULL)
        return;

    munmap((char *)txlines->text, txlines->text_len);
    free((char **)txlines->lines);
}

int compare_lines(const void* a, const void* b)
{
    assert(a != NULL);
    assert(b != NULL);
    const Line *a_line = (const Line*) a;
    const Line *b_line = (const Line*) b;

    assert(a_line->line != NULL);
    assert(b_line->line != NULL);

    const char *a_str = a_line->line;
    const char *b_str = b_line->line;

    while ((*a_str) && (*b_str))
    {
        while((*a_str) && !isalnum(*a_str)) a_str++;
        while((*b_str) && !isalnum(*b_str)) b_str++;

        int diff = tolower(*a_str) - tolower(*b_str);
        if (diff != 0)
            return diff;
        
        a_str++;
        b_str++;
    }
    return tolower(*a_str) - tolower(*b_str);
}

int compare_lines_inverse(const void *a, const void *b)
{
    assert(a != NULL);
    assert(b != NULL);
    const Line *a_line = (const Line*) a;
    const Line *b_line = (const Line*) b;

    assert(a_line->line != NULL);
    assert(b_line->line != NULL);

    const char *a_str = a_line->line + a_line->line_length - 1;
    const char *b_str = b_line->line + b_line->line_length - 1;

    do
    {
        while(a_str > a_line->line && !isalnum(*a_str)) a_str--;
        while(b_str > b_line->line && !isalnum(*b_str)) b_str--;

        if (a_str <= a_line->line ||
            b_str <= b_line->line)
            break;

        int c_a = isalnum(*a_str) ? tolower(*a_str) : 0;
        int c_b = isalnum(*b_str) ? tolower(*b_str) : 0;

        int diff = c_a - c_b;
        if (diff != 0)
            return diff;
        
        a_str--;
        b_str--;
    } while (a_str > a_line->line &&
             b_str > b_line->line);
    
    int c_a = isalnum(*a_str) ? tolower(*a_str) : 0;
    int c_b = isalnum(*b_str) ? tolower(*b_str) : 0;
    
    if (c_a == c_b)
        return (a_str > a_line->line)
             - (b_str > b_line->line);

    return c_a - c_b;
}
