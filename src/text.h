#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>

struct line_t {
        char *first_ch = nullptr;
        char  *last_ch = nullptr;
};

struct text_t {
        char **filename     = nullptr;
        char *buffer        = nullptr;
        size_t buf_size     = 0;
        line_t *lines       = {};
        size_t num_of_lines = 0;
};

// Creates and initializes buffer for storing text.
void create_text_buffer(FILE *infile, text_t *text);
// Creates and initializes an array of line_t values.
void create_lines_arr(text_t *text, bool verbose);
// Frees allocated with malloc()/calloc()/realloc()/etc. space.
void destroy_text(text_t *text);

#endif // TEXT_H

