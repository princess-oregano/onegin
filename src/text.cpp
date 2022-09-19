#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "sort.h"
#include "UI.h"
#include "text.h"

void create_text_buffer(FILE *infile, char **filename, char **dest_buffer, size_t *dest_buffer_size)
{
        assert(infile);
        assert(dest_buffer);
        assert(dest_buffer_size);

        struct stat stats {};
        stat(*filename, &stats);

        char *buffer = nullptr;
        size_t ch_scanned = 0;
        size_t num_of_ch = (size_t) stats.st_size;

        /*
         *if ((buffer = (char *) calloc(num_of_ch + 1, sizeof(char))) != nullptr) {
         *        ch_scanned = fread(buffer, sizeof(char), num_of_ch, infile);
         *        buffer[num_of_ch] = '\0';
         *} else {
         *        fprintf(stderr, "Error: Couldn't allocate memory.\n");
         *}
         */

        if ((buffer = (char *) mmap(NULL, num_of_ch, PROT_READ, MAP_PRIVATE, fileno(infile), 0)) == MAP_FAILED)
                fprintf(stderr, "Error: Couldn't allocate memory.\n");

        *dest_buffer_size = num_of_ch;
        *dest_buffer = buffer;
}

void create_lines_arr(char *buffer, line_t **lines, size_t *num_of_lines, size_t buf_size, bool verbose)
{
        assert(buffer);
        assert(lines);
        assert(num_of_lines);
        assert(buf_size);

        size_t i = 0;
        size_t line_count = 0;
        size_t line_array_count = 0;
        line_t *lines_array = nullptr;

        while (true) {
                if (buffer[i] == '\n' || buffer[i] == '\0') {
                        //fprintf(stderr,"Newline\n");
                        line_count++;
                }

                if (buffer[i] == '\0')
                        break;

                i++;
        }

        print_verbose_msg(verbose, "line_count = %d\n", line_count);

        if ((lines_array = (line_t *) calloc(line_count, sizeof(line_t))) == nullptr) {
                fprintf(stderr, "Couldn't allocate memory for lines_array.\n");
                return;
        }

        int ch = 0;
        for (line_array_count = 0, i = 0; line_array_count < line_count && i < buf_size; ) {
                //fprintf(stderr, "i = %d, buffer_size = %d\n", i, buffer_size);
                while (isspace(ch = buffer[i]))
                        i++;

                if (ch != '\n' && ch != '\0') {
                        lines_array[line_array_count].first_ch = &buffer[i];

                        while (ch != '\n' && ch != '\0') {
                                i++;
                                ch = buffer[i];
                        }

                        lines_array[line_array_count].last_ch = (&buffer[i]);

                        //fprintf(stderr, "Line %d initialized: %p.\n", line_array_count, &lines_array[line_array_count]);

                        line_array_count++;
                }
        }

        *lines = lines_array;
        *num_of_lines = line_array_count;
}

void destroy_text(text_t *text)
{
        assert(text);

        free(text->lines);
        munmap(text->buffer, text->buf_size);
        //free(text->buffer);
}

