#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include "text.h"
#include "UI.h"

// Bubble sort for strigs.
void bubble_sort_strings(void *ptr, size_t count, size_t size, int (*comp)(const void *, const void *));
// Quicksort for strings.
void  quick_sort_strings(void *ptr, size_t count, size_t size, int (*comp)(const void *, const void *));
// Sorts strings with given parameters.
void sort_strings(text_t *text, sort_params_t sort_params, bool verbose);

#endif // SORT_H

