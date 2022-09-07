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

        if ((original_text = fopen("test.txt", "r")) != NULL && (sorted_text = fopen("sort.txt", "w")) != NULL) {
                init_buffer(original_text, &text.buffer, &text.buf_size);

                init_lines_arr(text.buffer, &text.lines, &text.num_of_lines, text.buf_size);

                string_sort(&text);

                print_strings(text, sorted_text);

                free(text.lines);
                free(text.buffer);

                fclose(original_text);
                fclose(sorted_text);
        } else {
                fprintf(stderr, "Error: Couldn't open files.\n");
        }

        return 0;
}

