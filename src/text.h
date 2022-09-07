#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>

struct line_t {
        char *first_ch = NULL;
        char  *last_ch = NULL;
};

struct text_t {
        char *buffer     = NULL;
        size_t buf_size  = 0;
        line_t *lines    = {};
        int num_of_lines = 0;
};

// Creates and initializes buffer for storing text.
void init_buffer(FILE *infile, char **dest_buffer, size_t *dest_buffer_size);
// Creates and initializes an array of line_t values.
void init_lines_arr(char *buffer, line_t **lines, int *num_of_lines, int buf_size);

#endif // TEXT_H

