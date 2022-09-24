#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include "UI.h"
#include "sort.h"

static void swap_lines(void *f_line, void *s_line, size_t size)
{
        assert(f_line);
        assert(s_line);

        char *line1 = (char *) f_line;
        char *line2 = (char *) s_line;

        for (size_t i = 0; i < size; i++) {
                char temp = *(line1 + i);
             *(line1 + i) = *(line2 + i);
             *(line2 + i) = temp;
        }
}

static int compare_lines_ignore_punc(const void *f_line, const void *s_line)
{
        assert(f_line);
        assert(s_line);

        line_t line1 = *((const line_t *) f_line);
        line_t line2 = *((const line_t *) s_line);

        while (true) {
                while (!isalnum(*line1.first_ch)) {
                        if (line1.first_ch == line1.last_ch)
                                break;
                        line1.first_ch++;
                }

                while (!isalnum(*line2.first_ch)) {
                        if (line2.first_ch == line2.last_ch)
                                break;
                        line2.first_ch++;
                }

                if (*line1.first_ch != *line2.first_ch)
                        break;

                if (line1.first_ch == line1.last_ch || line2.first_ch == line2.last_ch) {
                        return (int) (line1.last_ch - line1.first_ch)
                             - (int) (line2.last_ch - line2.first_ch);
                }

                line1.first_ch++;
                line2.first_ch++;
        }

        return *line1.first_ch - *line2.first_ch;
}

static int compare_lines_ignore_punc_rev(const void *f_line, const void *s_line)
{
        assert(f_line);
        assert(s_line);

        line_t line1 = *((const line_t *) f_line);
        line_t line2 = *((const line_t *) s_line);

        while (true) {
                while (!isalnum(*line1.last_ch)) {
                        if (line1.last_ch == line1.first_ch)
                                break;
                        line1.last_ch--;
                }

                while (!isalnum(*line2.last_ch)) {
                        if (line2.last_ch == line2.first_ch)
                                break;
                        line2.last_ch--;
                }

                if (*line1.last_ch != *line2.last_ch)
                        break;

                if (line1.last_ch == line1.first_ch || line2.last_ch == line2.first_ch) {
                        return (int) (line1.last_ch - line1.first_ch)
                             - (int) (line2.last_ch - line2.first_ch);
                }

                line1.last_ch--;
                line2.last_ch--;
        }

        return *line1.last_ch - *line2.last_ch;
}

static int compare_lines(const void *f_line, const void *s_line)
{
        assert(f_line);
        assert(s_line);

        line_t line1 = *((const line_t *) f_line);
        line_t line2 = *((const line_t *) s_line);

        while (true) {
                if (*line1.first_ch != *line2.first_ch)
                        return *line1.first_ch - *line2.first_ch;

                if (line1.first_ch == line1.last_ch || line2.first_ch == line2.last_ch) {
                        return (int) (line1.last_ch - line1.first_ch)
                             - (int) (line2.last_ch - line2.first_ch);
                }

                line1.first_ch++;
                line2.first_ch++;
        }
}

static int compare_lines_rev(const void *f_line, const void *s_line)
{
        assert(f_line);
        assert(s_line);

        line_t line1 = *((const line_t *) f_line);
        line_t line2 = *((const line_t *) s_line);

        while (true) {
                if (*line1.last_ch != *line2.last_ch)
                        return *line1.last_ch - *line2.last_ch;

                if (line1.last_ch == line1.first_ch || line2.last_ch == line2.first_ch) {
                        return (int) (line1.last_ch - line1.first_ch)
                             - (int) (line2.last_ch - line2.first_ch);
                }

                line1.last_ch--;
                line2.last_ch--;
        }
}

// Bubble sort for strigs.
static void bubble_sort_strings(void *ptr, size_t count, size_t size, int (*comp)(const void *, const void *))
{
        assert(ptr);
        assert(comp);

        char *lines = (char *) ptr;

        for (size_t i = 0; i < count; i++) {
                for (size_t j = i + 1; j < count; j++) {
                        if (comp(lines + i*size, lines + j*size) > 0) {
                                swap_lines(lines + i*size, lines + j*size, size);
                        }
                }
        }
}

// Quicksort for strings.
static void quick_sort_strings(void *ptr, size_t count, size_t size, int (*comp)(const void *, const void *))
{
        assert(ptr);
        assert(comp);

        char *lines = (char *) ptr;
        size_t i = 0;
        size_t piv = 0;

        if (count <= 1)
		return;

	for (i = 0; i < count; i++) {
		if (comp(lines + i*size, lines + (count - 1)*size) < 0) {
			swap_lines(lines + i*size, lines + piv*size, size);
                        piv++;
                }
	}
	swap_lines(lines + piv*size, lines + (count - 1)*size, size);

	quick_sort_strings(lines, piv++, sizeof(line_t), comp);
	quick_sort_strings(lines + piv*size, count - piv, sizeof(line_t), comp);
}

void sort_strings(text_t *text, const params_t *params)
{
        int (*comp)(const void *, const void *) = nullptr;
        void (*sort_func)(void *ptr, size_t count, size_t size,
                          int (*comp)(const void *, const void *)) = nullptr;

        verbose_msg(params->verbose, "ignore_punc = %d, sort_type = %d\n",
                                     params->ignore_punc, params->sort_type);

        if (!params->ignore_punc) {
                if (params->reverse_comp)
                        comp = compare_lines_rev;
                else
                        comp = compare_lines;
        } else {
                if (params->reverse_comp)
                        comp = compare_lines_ignore_punc_rev;
                else
                        comp = compare_lines_ignore_punc;
        }

        switch (params->sort_type) {
                case NO_SORT:
                        return;
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
                        assert(0 && "Invalid sorting option");
                        break;
        }

        sort_func(text->lines, text->num_of_lines, sizeof(line_t), comp);
}

