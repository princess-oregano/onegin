#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include "UI.h"
#include "sort.h"

static void swap_lines(line_t *line1, line_t *line2)
{
        assert(line1);
        assert(line2);

        line_t temp = *line1;
             *line1 = *line2;
             *line2 = temp;
}

static int compare_lines_ignore_punc(const void *f_line, const void *s_line)
{
        assert(f_line);
        assert(s_line);

        line_t line1 = *((const line_t *) f_line);
        line_t line2 = *((const line_t *) s_line);

        while (true) {
                while (!isalnum(*line1.first_ch)) {
                        if (*line1.first_ch == *line1.last_ch)
                                break;
                        line1.first_ch++;
                }

                while (!isalnum(*line2.first_ch)) {
                        if (*line2.first_ch == *line2.last_ch)
                                break;
                        line2.first_ch++;
                }

                if (*line1.first_ch != *line2.first_ch)
                        break;

                if (line1.first_ch == line1.last_ch || line2.first_ch == line2.last_ch)
                        break;

                line1.first_ch++;
                line2.first_ch++;
        }

        return *line1.first_ch - *line2.first_ch;
}

static int compare_lines(const void *f_line, const void *s_line)
{
        assert(f_line);
        assert(s_line);

        line_t line1 = *((const line_t *) f_line);
        line_t line2 = *((const line_t *) s_line);

        while (line1.first_ch != line1.last_ch && line2.first_ch != line2.last_ch) {
                if (*line1.first_ch != *line2.first_ch)
                        break;

                line1.first_ch++;
                line2.first_ch++;
        }

        return *line1.first_ch - *line2.first_ch;
}

void bubble_sort_strings(void *ptr, size_t count, size_t size, int (*comp)(const void *, const void *))
{
        assert(ptr);
        assert(comp);

        line_t *lines = (line_t *) ptr;

        for (size_t i = 0; i < count; i++) {
                for (size_t j = i + 1; j < count; j++) {
                        if (comp(&lines[i], &lines[j]) > 0) {
                                swap_lines(&lines[i], &lines[j]);
                        }
                }
        }
}

void quick_sort_strings(void *ptr, size_t count, size_t size, int (*comp)(const void *, const void *))
{
        assert(ptr);
        assert(comp);

        line_t *lines = (line_t *) ptr;
        size_t i = 0;
        size_t piv = 0;

        if (count <= 1)
		return;

	for (i = 0; i < count; i++) {
		if (comp(&lines[i], &lines[count - 1]) < 0)
			swap_lines(lines + i, lines + piv++);
	}
	swap_lines(lines + piv, lines + count - 1);

	quick_sort_strings(lines, piv++, sizeof(line_t), comp);
	quick_sort_strings(lines + piv, count - piv, sizeof(line_t), comp);
}

void sort_strings(text_t *text, sort_params_t sort_params, bool verbose)
{
        int (*comp)(const void *, const void *) = compare_lines_ignore_punc;
        void (*sort_func)(void *ptr, size_t count, size_t size, int (*comp)(const void *, const void *)) = bubble_sort_strings;

        if (!sort_params.ignore_punc)
                comp = compare_lines;

        switch (sort_params.sort_type) {
                case BUBBLE_SORT:
                        sort_func = bubble_sort_strings;
                        break;
                case QUICK_SORT:
                        sort_func = quick_sort_strings;
                        break;
                case Q_SORT:
                        sort_func = qsort;
                        break;
                default:
                        fprintf(stderr, "Invalid sorting option.\n");
                        break;
        }

        print_verbose_msg(verbose, "ignore_punc = %d, sort_type = %d\n", sort_params.ignore_punc, sort_params.sort_type);
        sort_func(text->lines, text->num_of_lines, sizeof(line_t), comp);
}

