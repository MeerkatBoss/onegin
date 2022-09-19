#include "comparators.h"
#include <stdlib.h>
#include <wctype.h>
#include <assert.h>
#include <wchar.h>

static size_t skip_not_alnum(const char *str,
                             size_t max_skip,
                             enum direction dir,
                             wchar_t *lst)
{
    size_t pos = 0;
    const unsigned char MASK = 0xC0; /*1100 0000 two highest bits*/
    const unsigned char CONTINUATION = 0x80; /*10xx xxxx UTF8 continuation byte*/

    for(pos = 0; pos < max_skip; pos++)
    {
        if ((*str & MASK) == CONTINUATION)
        {
            str += dir;
            continue;
        }

        int c_len = mbtowc(NULL, str, 0);   /*non-negative*/
        wchar_t wc = L'\0';
        mbtowc(&wc, str, (size_t)c_len);
        if (iswalnum((wint_t)wc))
        {
            *lst = wc;
            break;
        }
        
        str += dir * (long long) c_len;
    }
    return pos;
}

int bidirectional_compare_strings(const char* str1, size_t str1_len,
                               const char* str2, size_t str2_len,
                               enum direction dir)
{
    size_t index1 = 0, index2 = 0;

    // TODO: i think this implementation is a bit too convoluted
    //       for what it does (it's not as complex as this looks)
    //
    // See, if you can clean this up a bit?) (Mainly reduce number
    // of edge cases in this code)

    for(
        ;
        index1 < str1_len && index2 < str2_len;
        index1++, index2++, str1 += dir, str2 += dir
    )
    {
        wchar_t wc1 = L'\0', wc2 = L'\0';
        size_t skip1 = skip_not_alnum(str1, str1_len - index1, dir, &wc1);
        size_t skip2 = skip_not_alnum(str2, str2_len - index2, dir, &wc2);
        str1 += dir*(long long)skip1;
        str2 += dir*(long long)skip2;
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

        wint_t lwc1 = towlower((wint_t)wc1);
        wint_t lwc2 = towlower((wint_t)wc2);
        if (lwc1 != lwc2)
            return lwc1 < lwc2
                    ? -1
                    :  1;
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

    return bidirectional_compare_strings(
        a_line->line, a_line->line_length,
        b_line->line, b_line->line_length,
        FORWARD
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

    return bidirectional_compare_strings(
        a_line->line + a_line->line_length - 1, a_line->line_length,
        b_line->line + b_line->line_length - 1, b_line->line_length,
        BACKWARD
    );
}

int compare_lines_by_address(const void *a, const void *b)
{
    assert(a != NULL);
    assert(b != NULL);
    const Line *a_line = (const Line*) a;
    const Line *b_line = (const Line*) b;

    //TODO: do I need to compare `.line` or can I simply
    //compare `a` with `b`?
    if (a_line->line == b_line->line)
        return 0;
    return a_line->line < b_line->line
            ? -1
            :  1;
}