#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "text.h"
#include "UI.h"

int main(int argc, char *argv[])
{
        file_t src {};
        file_t dst {};
        text_t text {};
        params_t params {};

        int ret = 0;
        if ((ret = process_args(argc, argv, &params)))
                return ret;

        if (params.help)
                return 0;

        if ((get_file(params.src_filename, &src, "r") == ERR_STATS) ||
            (get_file(params.dst_filename, &dst, "w") == ERR_STATS))
                return ERR_STATS;

        if (read_file(&text, &src, params.verbose) == ERR_ALLOC)
                return ERR_ALLOC;

        fclose(src.file_ptr);

        if (create_lines_arr(&text, params.verbose) == ERR_ALLOC)
                return ERR_ALLOC;

        sort_strings(&text, &params);

        if (write_strings(text, &src, &dst) == ERR_ALLOC)
                return ERR_ALLOC;

        destroy_text(&text);
        fclose(dst.file_ptr);

        return 0;
}

