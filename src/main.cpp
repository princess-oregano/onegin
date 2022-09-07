#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "text.h"
#include "output.h"

int main()
{
        FILE *original_text = NULL;
        FILE *sorted_text = NULL;
        text_t text {};

        if ((original_text = fopen("test.txt", "r")) == NULL) {
                fprintf(stderr, "Error: Couldn't open test.txt.\n");

                return 1;
        }

        if ((sorted_text = fopen("sort.txt", "w")) == NULL) {
                fprintf(stderr, "Error: Couldn't open sort.txt.\n");

                return 1;
        }

        init_buffer(original_text, &text.buffer, &text.buf_size);

        init_lines_arr(text.buffer, &text.lines, &text.num_of_lines, text.buf_size);

        quicksort_strings(text.lines, text.num_of_lines);

        print_strings(text, sorted_text);

        free(text.lines);
        free(text.buffer);

        fclose(original_text);
        fclose(sorted_text);

        return 0;
}

