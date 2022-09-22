#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "text.h"
#include "output.h"
#include "UI.h"

int main(int argc, char *argv[])
{
        file_t file {};
        text_t text {};
        params_t params {};

        int rev = 0;
        if ((rev = process_args(argc, argv, &params, &file)))
                return rev;

        if ((file.src_file_ptr = fopen(file.src_filename, "r")) == nullptr) {
                fprintf(stderr, "Error: Couldn't open %s.\n", file.src_filename);

                return ERR_OPEN_FILE;
        }

        if ((file.dst_file_ptr = fopen(file.dst_filename, "w")) == nullptr) {
                fprintf(stderr, "Error: Couldn't open %s.\n", file.dst_filename);

                return ERR_OPEN_FILE;
        }

        if (read_file(&text, &file, params.verbose) == ERR_ALLOC)
                return ERR_ALLOC;
        fclose(file.src_file_ptr);

        if (create_lines_arr(&text, params.verbose) == ERR_ALLOC)
                return ERR_ALLOC;

        sort_strings(&text, params);
        write_strings(text, &file);

        destroy_text(&text);
        fclose(file.dst_file_ptr);

        return 0;
}

