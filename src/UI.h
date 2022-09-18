#ifndef ARGS_H
#define ARGS_H

#include "sort.h"

enum error_t {
        ERR_FILE     = 1,
        ERR_PARAMS   = 2,
        ERR_ALLOC    = 3,
        ERR_SORT_OPT = 4,
};

// Processes command line arguments.
int process_args(int argc, char *argv[], FILE **original_text, FILE **sorted_text, sort_params_t *sort_params);
// Prints error message.
void print_err_msg(error_t err);

#endif // ARGS_H

