#include <assert.h>
#include "sort.h"

static void swap_lines(line_t *line1, line_t *line2)
{
        assert(line1);
        assert(line2);

        line_t temp = *line1;
             *line1 = *line2;
             *line2 = temp;
}

static int compare_lines(line_t line1, line_t line2)
{
        while (line1.first_ch != line1.last_ch && line2.first_ch != line2.last_ch) {
                if (*line1.first_ch != *line2.first_ch)
                        break;

                line1.first_ch++;
                line2.first_ch++;
        }

        return *line1.first_ch - *line2.first_ch;
}

void bubble_sort_strings(text_t *text)
{
        assert(text);

        for (int i = 0; i < text->num_of_lines; i++)
                for (int j = i + 1; j < text -> num_of_lines; j++) {
                        if (compare_lines(text->lines[i], text->lines[j]) > 0) {
                                fprintf(stderr, "swap\n");
                                swap_lines(&text->lines[i], &text->lines[j]);
                        }
                }
}

void quicksort_strings(line_t *lines, int num_of_lines)
{
        assert(lines);

	int i = 0;
        int piv = 0;

        if (num_of_lines <= 1)
		return;

	for (i = 0; i < num_of_lines; i++) {
		if (compare_lines(lines[i], lines[num_of_lines -1]) < 0)
			swap_lines(lines + i, lines + piv++);
	}
	swap_lines(lines + piv, lines + num_of_lines - 1);

	quicksort_strings(lines, piv++);
	quicksort_strings(lines + piv, num_of_lines - piv);
}

