#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "sort.h"
#include "UI.h"
#include "text.h"

void create_text_buffer(FILE *infile, text_t *text)
{
        assert(infile);
        assert(text);

        struct stat stats {};
        stat(*text->filename, &stats);

        char *buffer = nullptr;
        size_t num_of_ch = (size_t) stats.st_size;

        /*
         * size_t ch_scanned = 0;
         * if ((buffer = (char *) calloc(num_of_ch + 1, sizeof(char))) != nullptr) {
         *         ch_scanned = fread(buffer, sizeof(char), num_of_ch, infile);
         *         buffer[num_of_ch] = '\0';
         * } else {
         *         fprintf(stderr, "Error: Couldn't allocate memory.\n");
         * }
         */

        if ((buffer = (char *) mmap(NULL, num_of_ch, PROT_READ, MAP_PRIVATE, fileno(infile), 0)) == MAP_FAILED)
                fprintf(stderr, "Error: Couldn't allocate memory.\n");

        text->buf_size = num_of_ch;
        text->buffer = buffer;
}

void create_lines_arr(text_t *text, bool verbose)
{
        assert(text);

        size_t i = 0;
        size_t line_count = 0;
        size_t line_array_count = 0;
        line_t *lines_array = nullptr;

        while (true) {
                if (text->buffer[i] == '\n' || text->buffer[i] == '\0') {
                        //fprintf(stderr,"Newline\n");
                        line_count++;
                }

                if (text->buffer[i] == '\0')
                        break;

                i++;
        }

        verbose_msg(verbose, "line_count = %d\n", line_count);

        if ((lines_array = (line_t *) calloc(line_count, sizeof(line_t))) == nullptr) {
                fprintf(stderr, "Couldn't allocate memory for lines_array.\n");
                return;
        }

        int ch = 0;
        for (line_array_count = 0, i = 0; line_array_count < line_count && i < text->buf_size; ) {
                //fprintf(stderr, "i = %d, buffer_size = %d\n", i, buffer_size);
                while (isspace(ch = text->buffer[i]))
                        i++;

                if (ch != '\n' && ch != '\0') {
                        lines_array[line_array_count].first_ch = &text->buffer[i];

                        while (ch != '\n' && ch != '\0') {
                                i++;
                                ch = text->buffer[i];
                        }

                        lines_array[line_array_count].last_ch = (&text->buffer[i]);

                        //fprintf(stderr, "Line %d initialized: %p.\n", line_array_count, &lines_array[line_array_count]);

                        line_array_count++;
                }
        }

        text->lines = lines_array;
        text->num_of_lines = line_array_count;
}

void destroy_text(text_t *text)
{
        assert(text);

        if (text->lines != nullptr)
                free(text->lines);
        if (text->buffer != nullptr)
                munmap(text->buffer, text->buf_size);
        //free(text->buffer);
}

