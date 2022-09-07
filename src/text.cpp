#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "text.h"

void init_buffer(FILE *infile, char **dest_buffer, size_t *dest_buffer_size)
{
        assert(infile);
        assert(dest_buffer);
        assert(dest_buffer_size);

        int long num_of_ch = 0;
        char *buffer = NULL;
        size_t ch_scanned = 0;

        fseek(infile, 0, SEEK_END);
        num_of_ch = ftell(infile);
        rewind(infile);

        if ((buffer = (char *) calloc(num_of_ch + 1, sizeof(char))) != NULL) {
                ch_scanned = fread(buffer, sizeof(char), num_of_ch, infile);
                buffer[num_of_ch] = '\0';
        } else {
                fprintf(stderr, "Error.\n");
        }

        *dest_buffer_size = ch_scanned;
        *dest_buffer = buffer;
}

void init_lines_arr(char *buffer, line_t **lines, int *num_of_lines, int buf_size)
{
        assert(buffer);
        assert(lines);
        assert(num_of_lines);
        assert(buf_size);

        int i = 0;
        int ch = 0;
        int line_count = 0;
        char *buf = buffer;
        int line_array_count = 0;

        while (true) {
                if (buf[i] == '\n' || buf[i] == '\0') {
                        //fprintf(stderr,"Newline\n");
                        line_count++;
                }

                if (buf[i] == '\0')
                        break;

                i++;
        }

        fprintf(stderr, "line_count = %d\n", line_count);

        line_t *lines_array = (line_t *) calloc(line_count, sizeof(line_t));

        for (line_array_count = 0, i = 0; line_array_count < line_count && i < buf_size; ) {
                fprintf(stderr, "i = %d, buf_size = %d", i, buf_size);
                while (isspace(ch = buf[i]))
                        i++;

                if (ch == EOF) {
                        //fprintf(stderr, "EOF encountered\n");
                        break;
                }

                if (ch != '\n' && ch != '\0') {
                        lines_array[line_array_count].first_ch = &buf[i];

                        while (ch != '\n' && ch != '\0') {
                                i++;
                                ch = buf[i];
                        }

                        lines_array[line_array_count].last_ch = (&buf[i]);

                        fprintf(stderr, "Line %d initialized: %p.\n", line_array_count, &lines_array[line_array_count]);

                        line_array_count++;
                }
        }

        fprintf(stderr, "Cycle broken\n");
        *lines = lines_array;
        *num_of_lines = line_array_count;
}

void free_space(text_t *text)
{
        free(text->lines);
        free(text->buffer);
}

