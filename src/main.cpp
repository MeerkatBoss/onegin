#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "sorting.h"
#include "text_lines.h"
#include "text_utils.h"
#include <ctype.h>

int main()
{
    // TODO: Ok, as a fast solution, but IMO not enough for a final version)
    setlocale(LC_CTYPE, "ru_RU.cp1251");

    Line arr[10] = //TODO: extract tests
    {
        {.line_number = 0, .line_length = 6, .line = "abbbab"},
        {.line_number = 1, .line_length = 12, .line = "   ababab  ,"},
        {.line_number = 2, .line_length = 5, .line = "aaaaa"},
        {.line_number = 3, .line_length = 6, .line = " babab"},
        {.line_number = 4, .line_length = 5, .line = " bab."},
        {.line_number = 5, .line_length = 5, .line = "babaa"},
        {.line_number = 6, .line_length = 7, .line = " abaab!"},
        {.line_number = 7, .line_length = 6, .line = "bbbbaa"},
        {.line_number = 8, .line_length = 6, .line = "bbbaaa"},
        {.line_number = 9, .line_length = 6, .line = "baaaaa"}
    };
    insertion_sort(arr, 10, sizeof(*arr), compare_lines_inverse);
    for (int i = 0; i<10; i++)
        puts(arr[i].line);
    
    // TODO: Why name this "tlines"?) Terminator Lines? I'LL BE BACK!
    //       if you'd just name it "text" or "lines" or "text_lines",
    //       it would be less confusing.
    TextLines tlines = read_file("IO/onegin.txt");
    // TODO:                      ^~ Not really an "IO",
    //       more like "resources" or "data" or whatever, just not IO
    //
    // Also, "IO" (with all capitals), breaks your naming
    // convention (of naming dirs in lowercase)
    if (tlines.text == NULL)
    {
        perror("Error reading input file");
        return 1;
    }

    FILE *output = fopen("IO/result.txt", "w");
    if (output == NULL)
    {
        perror("Error opening output file");
        return 1;
    }

    fputs("==LEXICOGRAPHIC SORT:==\n", output);
    qsort(tlines.lines, tlines.line_count,
                sizeof(*tlines.lines), compare_lines);
    print_lines(tlines.lines, tlines.line_count, output);

    fputs("==LINE END LEXICOGRAPHIC SORT:==\n", output);
    insertion_sort(tlines.lines, tlines.line_count,
                    sizeof(*tlines.lines), compare_lines_inverse);
    print_lines(tlines.lines, tlines.line_count, output);

    fputs("==ORIGINAL TEXT==\n", output);
    qsort(tlines.lines, tlines.line_count,
                sizeof(*tlines.lines), compare_lines_by_number);
    print_lines(tlines.lines, tlines.line_count, output);
    
    fclose(output);
    dispose_lines(&tlines);

    return 0;
}
