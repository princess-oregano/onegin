#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "text.h"
#include "output.h"
#include "args.h"

int main(int argc, char *argv[])
{
        FILE *original_text = NULL;
        FILE *sorted_text = NULL;
        text_t text {};
        sort_params_t sort_params {};

        process_args(argc, argv, &original_text, &sorted_text, &sort_params);

        init_buffer(original_text, &text.buffer, &text.buf_size);
        fclose(original_text);

        init_lines_arr(text.buffer, &text.lines, &text.num_of_lines, text.buf_size);

        sort_strings(&text, sort_params);
        print_strings(text, sorted_text, argv[1]);

        free_space(&text);
        fclose(sorted_text);

        return 0;
}

