#include "sort.h"

static void swap_lines(line_t *line1, line_t *line2)
{
        line_t temp = {};

          temp = *line1;
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

void string_sort(text_t *text)
{
       for (int i = 0; i < text->num_of_lines; i++)
               for (int j = i + 1; j < text -> num_of_lines; j++) {
                       if (compare_lines(text->lines[i], text->lines[j]) > 0) {
                                fprintf(stderr, "swap\n");
                                swap_lines(&text->lines[i], &text->lines[j]);
                       }
               }
}

