#include <string.h>
#include "args.h"
#include "sort.h"

void process_args(int argc, char *argv[], sort_params_t *sort_params)
{
        if (argc < 3) {
                fprintf(stderr, "Error: not enough parameters.\n");

                return;
        }

        for (int i = 3; i < argc; i++) {
                if (strcmp(argv[i], "-p") == 0)
                        sort_params->ignore_punc = false;
        }
}

