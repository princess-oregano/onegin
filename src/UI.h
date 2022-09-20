#ifndef ARGS_H
#define ARGS_H

#include <stdio.h>
#include "text.h"

enum sort_t {
        BUBBLE_SORT = 0,
        QUICK_SORT  = 1,
        Q_SORT      = 2,
};

struct sort_params_t {
        bool ignore_punc = true;
        sort_t sort_type = QUICK_SORT;
};

enum error_t {
        ERR_NO_ERR   = 0,
        ERR_FILE     = 1,
        ERR_PARAMS   = 2,
        ERR_ALLOC    = 3,
        ERR_SORT_OPT = 4,
};

// Processes command line arguments.
error_t process_args(int argc, char *argv[], FILE **original_text, FILE **sorted_text, sort_params_t *sort_params, text_t *text, bool *verbose);
// Prints error message.
void print_err_msg(error_t err);
// Prints info about program processes in verbose mode.
int verbose_msg(bool verbose, const char *format, ...);

#endif // ARGS_H

