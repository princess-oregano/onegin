#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include "text.h"

// Bubble sort for strigs.
void bubble_sort_strings(text_t *text);
// Quicksort for strings.
void quick_sort_strings(line_t *lines, int num_of_lines);

#endif // SORT_H

