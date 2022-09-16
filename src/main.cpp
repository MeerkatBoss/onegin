#include <stdio.h>
#include "sorting.h"
#include "text_lines.h"

int main()
{
    Line arr[10] = 
    {
        {.line_number = 0, .line_length = 6, .line = "abbbab"},
        {.line_number = 1, .line_length = 6, .line = "ababab"},
        {.line_number = 2, .line_length = 5, .line = "aaaaa"},
        {.line_number = 3, .line_length = 5, .line = "babab"},
        {.line_number = 4, .line_length = 3, .line = "bab"},
        {.line_number = 5, .line_length = 5, .line = "babaa"},
        {.line_number = 6, .line_length = 5, .line = "abaab"},
        {.line_number = 7, .line_length = 6, .line = "bbbbaa"},
        {.line_number = 8, .line_length = 6, .line = "bbbaaa"},
        {.line_number = 9, .line_length = 6, .line = "baaaaa"}
    };
    insertion_sort(arr, 10, sizeof(*arr), compare_lines_inverse);
    for (int i = 0; i<10; i++)
        puts(arr[i].line);
    //return 0;

    const TextLines tlines = read_file("hamlet.txt");
    insertion_sort(tlines.lines, tlines.line_count,
                    sizeof(*tlines.lines), compare_lines_inverse);
    
    FILE *output = fopen("result.txt", "w");
    for (size_t i = 0; i < tlines.line_count; i++)
    {
        fprintf(output, "%4zu: %s\n",
                tlines.lines[i].line_number,
                tlines.lines[i].line);
    }
    fclose(output);
    return 0;
}