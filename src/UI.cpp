#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "UI.h"
#include "sort.h"

int verbose_msg(bool verbose, const char *format, ...)
{
        if (!verbose)
                return 0;

        va_list args;
        va_start(args, format);
        int ret = vfprintf(stderr, format, args);
        va_end(args);

        return ret;
}

error_t process_args(int argc, char *argv[], FILE **original_text, FILE **sorted_text, sort_params_t *sort_params, text_t *text, bool *verbose)
{
        for (int i = 1; i < argc; i++) {
                if (strcmp(argv[i], "-i") == 0) {
                        if ((*original_text = fopen(argv[++i], "r")) == nullptr) {
                                fprintf(stderr, "Error: Couldn't open %s.\n", argv[i]);

                                return ERR_FILE;
                        } else {
                                text->filename = &argv[i];
                        }
                } else if (strcmp(argv[i], "-o") == 0) {
                        if ((*sorted_text = fopen(argv[++i], "w")) == nullptr) {
                                fprintf(stderr, "Error: Couldn't open %s.\n", argv[i]);

                                return ERR_FILE;
                        }
                } else if (strcmp(argv[i], "-p") == 0) {
                        sort_params->ignore_punc = false;
                } else if (strcmp(argv[i], "-s") == 0) {
                        i++;
                        if (strcmp(argv[i], "-b") == 0) {
                                sort_params->sort_type = BUBBLE_SORT;
                        }
                        else if (strcmp(argv[i], "-q") == 0) {
                                sort_params->sort_type = QUICK_SORT;
                        }
                        else if (strcmp(argv[i], "-qs") == 0) {
                                sort_params->sort_type = Q_SORT;
                        }
                        else {
                                fprintf(stderr, "Error: Wrong sorting options.\n");
                                return ERR_SORT_OPT;
                        }
                } else if (strcmp(argv[i], "-v") == 0) {
                        *verbose = true;
                } else {
                        fprintf(stderr, "Error: Wrong parameters.\n");
                        return ERR_PARAMS;
                }
        }

        return ERR_NO_ERR;
}

