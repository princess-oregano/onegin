#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "UI.h"
#include "sort.h"
#include "text.h"

int read_file(text_t *text, file_t *file, bool verbose)
{
        assert(text);
        assert(file);

        struct stat stats {};
        stat(file->src_filename, &stats);

        text->buf_size = (size_t) stats.st_size;

        char *buffer = nullptr;
        if ((buffer = (char *) mmap(NULL, text->buf_size, PROT_READ, MAP_PRIVATE, fileno(file->src_file_ptr), 0)) == MAP_FAILED) {
                fprintf(stderr, "Error: Couldn't allocate memory.\n");
                return ERR_ALLOC;
        }

        verbose_msg(verbose, "Buffer pointer: %p\n", buffer);
        text->buffer = buffer;

        return ERR_NO_ERR;
}

int create_lines_arr(text_t *text, bool verbose)
{
        assert(text);

        size_t i = 0;
        size_t line_count = 0;
        line_t *lines_array = nullptr;

        while (true) {
                if (text->buffer[i] == '\n' || text->buffer[i] == '\0')
                        line_count++;

                if (text->buffer[i] == '\0')
                        break;

                i++;
        }

        verbose_msg(verbose, "line_count = %d\n", line_count);

        if ((lines_array = (line_t *) calloc(line_count, sizeof(line_t))) == nullptr) {
                fprintf(stderr, "Couldn't allocate memory for lines_array.\n");
                return ERR_ALLOC;
        }

        int ch = 0;
        size_t index = 0;
        for (index = 0, i = 0; index < line_count && i < text->buf_size; ) {
                while (isspace(ch = text->buffer[i]))
                        i++;

                if (ch != '\n' && ch != '\0') {
                        lines_array[index].first_ch = &text->buffer[i];

                        while (ch != '\n' && ch != '\0') {
                                i++;
                                ch = text->buffer[i];
                        }

                        lines_array[index].last_ch = (&text->buffer[i]);

                        index++;
                }
        }

        text->lines = lines_array;
        text->num_of_lines = index;

        return ERR_NO_ERR;
}

void destroy_text(text_t *text)
{
        assert(text);

        if (text->lines != nullptr)
                free(text->lines);
        if (text->buffer != nullptr)
                munmap(text->buffer, text->buf_size);
}

