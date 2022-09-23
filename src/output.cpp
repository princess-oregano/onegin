#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include "UI.h"
#include "output.h"

error_t write_strings(text_t text, file_t *file)
{
        size_t count = 0;
        struct stat stats {};
        stat(file->src_filename, &stats);

        setvbuf(file->dst_file_ptr, NULL, _IONBF, 0);

        char *sorted_text_buffer = nullptr;
        if((sorted_text_buffer = (char *) calloc((size_t) stats.st_size, sizeof(char))) == nullptr)
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

        fwrite(sorted_text_buffer, sizeof(char), count, file->dst_file_ptr);
        free(sorted_text_buffer);

        return ERR_NO_ERR;
}

