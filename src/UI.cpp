#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "UI.h"
#include "sort.h"

static void set_verbose(bool *verbose)
{
        *verbose = true;
}

int print_verbose_msg(bool verbose, const char *format, ...)
{
        if (!verbose)
                return 0;

        va_list args;
        va_start(args, format);
        int ret = vfprintf(stderr, format, args);
        va_end(args);

        return ret;
}

int process_args(int argc, char *argv[], FILE **original_text, FILE **sorted_text, sort_params_t *sort_params, bool *verbose)
{
        if (argc < 3) {
                fprintf(stderr, "Error: not enough parameters.\n");

                return ERR_PARAMS;
        }

        if ((*original_text = fopen(argv[1], "r")) == nullptr) {
                fprintf(stderr, "Error: Couldn't open %s.\n", argv[1]);

                return ERR_FILE;
        }

        if ((*sorted_text = fopen(argv[2], "w")) == nullptr) {
                fprintf(stderr, "Error: Couldn't open %s.\n", argv[2]);

                return ERR_FILE;
        }

        for (int i = 3; i < argc; i++) {
                if (strcmp(argv[i], "-p") == 0)
                        sort_params->ignore_punc = false;
                if (strcmp(argv[i], "-b") == 0)
                        sort_params->sort_type = BUBBLE_SORT;
                if (strcmp(argv[i], "-q") == 0)
                        sort_params->sort_type = QUICK_SORT;
                if (strcmp(argv[i], "-qs") == 0)
                        sort_params->sort_type = Q_SORT;
                if (strcmp(argv[i], "-v") == 0)
                        set_verbose(verbose);
        }

        return ERR_NO_ERR;
}

