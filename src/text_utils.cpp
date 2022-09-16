#include "text_utils.h"
#include <assert.h>

void print_lines(const Line *lines, size_t line_count, FILE *stream)
{
    assert(lines != NULL);
    assert(stream != NULL);

    for (size_t i = 0; i < line_count; i++)
    {
        fprintf(stream, "%4zu: %s\n",
                lines[i].line_number,
                lines[i].line);
    }
    putc('\n', stream);
}
