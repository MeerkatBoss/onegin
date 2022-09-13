#include <stdio.h>
#include "sorting.h"
#include "text_lines.h"

int main()
{
    const char *arr[10] = 
    {
        "aaaab",
        "aa",
        "aaaaa",
        "baab",
        "bab",
        "baba",
        "abab",
        "bbbbaa",
        "bbbaaa",
        "baaaaa"
    };
    insertion_sort(arr, arr+10, sizeof(char*), compare_strings);
    for (int i = 0; i<10; i++)
        puts(arr[i]);

    const TextLines *tlines = read_file("hamlet.txt");
    insertion_sort(tlines->lines, tlines->lines + tlines->line_count,
                    sizeof(char*), compare_strings);
    
    FILE *output = fopen("result.txt", "w");
    for (int i = 0; i < tlines->line_count; i++)
    {
        fputs(tlines->lines[i], output);
        fputc('\n', output);
    }
    fclose(output);
    return 0;
}