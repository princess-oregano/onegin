#ifndef ARGS_H
#define ARGS_H

#include <stdio.h>
#include <sys/stat.h>

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
        ERR_STATS     = 4,
        ERR_ALLOC     = 5,
};

struct file_t {
        FILE  *file_ptr = nullptr;
        struct stat file_stats = {};
};

struct params_t {
        char *src_filename = nullptr;
        char *dst_filename = nullptr;
        sort_t sort_type  = QUICK_SORT;
        bool help         = false;
        bool verbose      = false;
        bool ignore_punc  = true;
        bool reverse_comp = false;
};

// Processes command line arguments.
error_t process_args(int argc, char *argv[], params_t *params);
// Prints error message.
void print_err_msg(error_t err);
// Prints info about program processes in verbose mode.
int verbose_msg(bool verbose, const char *format, ...);
// Opens file and gets info about it.
error_t get_file(char *filename, file_t *file, const char *mode);

#endif // ARGS_H

