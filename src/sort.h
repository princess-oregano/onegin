#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include "text.h"

// Bubble sort for strigs.
void bubble_sort_strings(text_t *text);
// Quicksort for strings.
void quick_sort_strings(void *ptr, size_t count, size_t size, int (*comp)(const void *, const void *));
void sort_strings(text_t *text);

#endif // SORT_H

