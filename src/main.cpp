#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "text.h"
#include "output.h"
#include "UI.h"

int main(int argc, char *argv[])
{
        FILE *original_text = nullptr;
        FILE *sorted_text = nullptr;
        text_t text {};
        sort_params_t sort_params {};
        bool verbose = false;

        process_args(argc, argv, &original_text, &sorted_text, &sort_params, &text, &verbose);

        create_text_buffer(original_text, text.filename, &text.buffer, &text.buf_size);
        fclose(original_text);

        create_lines_arr(text.buffer, &text.lines, &text.num_of_lines, text.buf_size, verbose);

        sort_strings(&text, sort_params, verbose);
        write_strings(text, sorted_text, text.filename);

        destroy_text(&text);
        fclose(sorted_text);

        return 0;
}

