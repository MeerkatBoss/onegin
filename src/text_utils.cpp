#include <assert.h>

#include "text_utils.h"

void print_lines(const Line *lines, size_t line_count, FILE *stream)
{
    assert(lines != NULL);
    assert(stream != NULL);

    for (size_t i = 0; i < line_count; i++)
    {
        fputs(lines[i].line, stream);
        fputc('\n', stream);
    }
    fputc('\n', stream);
}
