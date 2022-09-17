#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include "text.h"

enum sort_t {
        BUBBLE_SORT = 0,
        QUICK_SORT  = 1,
        Q_SORT      = 2,
};

struct sort_params_t {
        bool ignore_punc = true;
        sort_t sort_type = BUBBLE_SORT;
};

// Bubble sort for strigs.
void bubble_sort_strings(void *ptr, size_t count, size_t size, int (*comp)(const void *, const void *));
// Quicksort for strings.
void quick_sort_strings(void *ptr, size_t count, size_t size, int (*comp)(const void *, const void *));
// Sorts strings with given parameters.
void sort_strings(text_t *text, sort_params_t sort_params);

#endif // SORT_H

