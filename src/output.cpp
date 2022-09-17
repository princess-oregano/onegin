#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include "output.h"

void print_strings(text_t text, FILE *stream, char *filename)
{
        assert(stream);

        int count = 0;
        struct stat stats {};
        stat(filename, &stats);

        setvbuf(stream, NULL, _IOFBF, stats.st_blksize);

        char *sorted_text_buffer = (char *) calloc(stats.st_size, sizeof(char));

        for (int i = 0; i < text.num_of_lines; i++) {
                assert(text.lines[i].first_ch);
                //fprintf(stderr, "Line passed: %p\n", &text.lines[i].first_ch);

                while (text.lines[i].first_ch != text.lines[i].last_ch) {
                        sorted_text_buffer[count] = *text.lines[i].first_ch;
                        text.lines[i].first_ch++;
                        count++;
                }

                sorted_text_buffer[count] = '\n';
                count++;
        }

        fwrite(sorted_text_buffer, sizeof(char), count, stream);
        free(sorted_text_buffer);
}

