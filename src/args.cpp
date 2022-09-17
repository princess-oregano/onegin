#include <string.h>
#include <assert.h>
#include "args.h"
#include "sort.h"

int process_args(int argc, char *argv[], FILE **original_text, FILE **sorted_text, sort_params_t *sort_params)
{
        if (argc < 3) {
                fprintf(stderr, "Error: not enough parameters.\n");

                return ERR_PARAMS;
        }

        if ((*original_text = fopen(argv[1], "r")) == NULL) {
                fprintf(stderr, "Error: Couldn't open %s.\n", argv[1]);

                return ERR_FILE;
        }

        if ((*sorted_text = fopen(argv[2], "w")) == NULL) {
                fprintf(stderr, "Error: Couldn't open %s.\n", argv[2]);

                return ERR_FILE;
        }

        for (int i = 3; i < argc; i++) {
                if (strcmp(argv[i], "-p") == 0)
                        sort_params->ignore_punc = false;
        }

        return -1;
}

