#include "text_lines.h"
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief Maps file lines to memory
 * 
 * @param[in] path - path to file
 * @param[out] file_size - pointer to file size
 * @return file contents
 */
static char* map_file(const char *path, size_t *file_size)
{
    assert(path != NULL);

    /* Open file descriptor */
    int fd = open(path, O_RDONLY);
    if (fd < 0) {/* Cannot open file, errno set by open */
        perror("Cannot open file.");
        return NULL;
    }

    /* Get file size */
    struct stat file_stat;
    if (fstat(fd, &file_stat) < 0) /* Cannot read file, errno set by fstat */
    {
        int tmp = errno;
        close(fd);
        errno = tmp;
        return NULL;
    }

    /* Call mmap */
    char *mapping = (char*) mmap( /* Map extra byte for '\0' */
        NULL, (size_t)file_stat.st_size + 1u,
        PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    close(fd);
    if (mapping == MAP_FAILED) /* Mapping failed, errno set by mmap */
    {
        perror("Failed to read file.");
        return NULL;
    }

    *file_size = (size_t)file_stat.st_size + 1u;
    return mapping;
}

const TextLines *read_file(const char *path)
{
    char *text = NULL;
    size_t text_len = 0;

    text = map_file(path, &text_len);

    if (text == NULL)
        return NULL;

    size_t line_count = 1;
    for (size_t i = 0; i < text_len - 1; i++) /* NUL-terminate each line */
        if (text[i] == '\n')
        {
            text[i] = '\0';
            line_count++;
        }
    text[text_len - 1] = '\0';

    char ** lines = (char**) calloc(line_count, sizeof(char*));
    char *last_line = text; /* Pointer to the beginning of last line */
    int line_num = 0;
    for (size_t i = 0; i < text_len; i++)
        if (text[i] == '\0') /* Line ended */
        {
            lines[line_num] = last_line; /* Store line */
            last_line = &text[i + 1]; /* Next line begins on i+1st position */
            line_num++; /* Increment line number */
        }

    /* Allocate struct */
    TextLines *txlines = (TextLines*) calloc(1, sizeof(TextLines));

    /* Store file contents */
    *txlines = {
            .text = (const char*) text,
            .text_len = text_len,
            .lines = (const char**) lines,
            .line_count = line_count
        };
    return txlines;
}

void close_reader(const TextLines *txlines)
{
    if (txlines == NULL)
        return;

    munmap((char *)txlines->text, txlines->text_len);
    free((char **)txlines->lines);
    free((void *)txlines);
}
