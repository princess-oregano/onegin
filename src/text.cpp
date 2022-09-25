#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "UI.h"
#include "sort.h"
#include "text.h"

int read_file(text_t *text, file_t *src, bool verbose)
{
        assert(text);
        assert(src);

        text->buf_size = (size_t) src->file_stats.st_size;

        char *buffer = nullptr;
        if ((buffer = (char *) mmap(NULL, text->buf_size, PROT_READ, MAP_PRIVATE,
                                    fileno(src->file_ptr), 0)) == MAP_FAILED) {

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
                fprintf(stderr, "Error: Couldn't allocate memory for lines_array.\n");
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

int write_strings(text_t text, file_t *src, file_t *dst)
{
        size_t count = 0;

        setvbuf(dst->file_ptr, NULL, _IONBF, 0);

        char *sorted_text_buffer = nullptr;
        if((sorted_text_buffer = (char *) calloc((size_t) src->file_stats.st_size,
                                                 sizeof(char))) == nullptr)
                return ERR_ALLOC;

        for (size_t i = 0; i < text.num_of_lines; i++) {
                assert(text.lines[i].first_ch);

                while (text.lines[i].first_ch != text.lines[i].last_ch) {
                        sorted_text_buffer[count] = *text.lines[i].first_ch;

                        text.lines[i].first_ch++;
                        count++;
                }

                sorted_text_buffer[count] = '\n';
                count++;
        }

        fwrite(sorted_text_buffer, sizeof(char), count, dst->file_ptr);
        free(sorted_text_buffer);

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

