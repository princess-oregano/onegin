#include <stdio.h>
#include <assert.h>
#include "output.h"

void print_strings(text_t text, FILE *stream)
{
        for (int i = 0; i < text.num_of_lines; i++) {
                assert(text.lines[i].first_ch);
                fprintf(stderr, "Line passed: %p\n", &text.lines[i].first_ch);
                fwrite(text.lines[i].first_ch, sizeof(char), text.lines[i].last_ch - text.lines[i].first_ch, stream);
                fwrite("\n", sizeof(char), 1, stream);
        }
}

