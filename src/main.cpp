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
        {.line_length = 6, .line = "abbbab"},
        {.line_length = 12, .line = "   ababab  ,"},
        {.line_length = 5, .line = "aaaaa"},
        {.line_length = 6, .line = " babab"},
        {.line_length = 5, .line = " bab."},
        {.line_length = 5, .line = "babaa"},
        {.line_length = 7, .line = " abaab!"},
        {.line_length = 6, .line = "bbbbaa"},
        {.line_length = 6, .line = "bbbaaa"},
        {.line_length = 6, .line = "baaaaa"}
    };
    insertion_sort(arr, 10, sizeof(*arr), compare_lines_inverse);
    for (int i = 0; i<10; i++)
        puts(arr[i].line);
    
    TextLines text_lines = read_file("data/onegin.txt");
    if (text_lines.text == NULL)
    {
        perror("Error reading input file");
        return 1;
    }

    FILE *output = fopen("output/onegin.txt", "w");
    if (output == NULL)
    {
        perror("Error opening output file");
        return 1;
    }

    fputs("==LEXICOGRAPHIC SORT:==\n", output);
    qsort(text_lines.lines, text_lines.line_count,
                sizeof(*text_lines.lines), compare_lines);
    print_lines(text_lines.lines, text_lines.line_count, output);

    fputs("==LINE END LEXICOGRAPHIC SORT:==\n", output);
    insertion_sort(text_lines.lines, text_lines.line_count,
                    sizeof(*text_lines.lines), compare_lines_inverse);
    print_lines(text_lines.lines, text_lines.line_count, output);

    fputs("==ORIGINAL TEXT==\n", output);
    qsort(text_lines.lines, text_lines.line_count,
                sizeof(*text_lines.lines), compare_lines_by_address);
    print_lines(text_lines.lines, text_lines.line_count, output);
    
    fclose(output);
    dispose_lines(&text_lines);

    return 0;
}
