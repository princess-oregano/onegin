#ifndef ARGS_H
#define ARGS_H

#include <stdio.h>

const int FILENAME_SIZE = 256;

enum sort_t {
        NO_SORT     = 0,
        BUBBLE_SORT = 1,
        QUICK_SORT  = 2,
        Q_SORT      = 3,
};

enum error_t {
        ERR_NO_ERR    = 0,
        ERR_OPEN_FILE = 1,
        ERR_PARAMS    = 2,
        ERR_SORT_OPT  = 3,
        ERR_ALLOC     = 4,
};

struct file_t {
        // stat?
        char  src_filename[FILENAME_SIZE] = {};
        FILE *src_file_ptr = nullptr;
        // large static array for name
        char  dst_filename[FILENAME_SIZE] = {};
        FILE *dst_file_ptr = nullptr;
};

struct params_t {
        sort_t sort_type  = QUICK_SORT;
        bool help         = false;
        bool verbose      = false;
        bool ignore_punc  = true;
        bool reverse_comp = false;
};

// Processes command line arguments.
error_t process_args(int argc, char *argv[], params_t *params, file_t *file);
// Prints error message.
void print_err_msg(error_t err);
// Prints info about program processes in verbose mode.
int verbose_msg(bool verbose, const char *format, ...);
// Prints help message.
void print_help();

#endif // ARGS_H

