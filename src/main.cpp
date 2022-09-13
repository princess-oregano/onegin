#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "text.h"
#include "output.h"

int main(int argc, char *argv[])
{
        FILE *original_text = NULL;
        FILE *sorted_text = NULL;
        text_t text {};

        if ((original_text = fopen(argv[1], "r")) == NULL) {
                fprintf(stderr, "Error: Couldn't open %s.\n", argv[1]);

                return 1;
        }

        if ((sorted_text = fopen(argv[2], "w")) == NULL) {
                fprintf(stderr, "Error: Couldn't open %s.\n", argv[2]);

                return 1;
        }

        init_buffer(original_text, &text.buffer, &text.buf_size);
        init_lines_arr(text.buffer, &text.lines, &text.num_of_lines, text.buf_size);

        quick_sort_strings(text.lines, text.num_of_lines);

        print_strings(text, sorted_text);

        free_space(&text);

        fclose(original_text);
        fclose(sorted_text);

        return 0;
}

