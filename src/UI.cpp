#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "UI.h"
#include "sort.h"

int verbose_msg(bool verbose, const char *format, ...)
{
        if (!verbose)
                return 0;

        va_list args;
        va_start(args, format);
        int ret = vfprintf(stderr, format, args);
        va_end(args);

        return ret;
}

error_t process_args(int argc, char *argv[], params_t *params, file_t *file)
{
        for (int i = 1; i < argc; i++) {
                if (strcmp(argv[i], "-i") == 0) {
                        strncpy(file->src_filename, argv[++i], FILENAME_SIZE - 1);
                } else if (strcmp(argv[i], "-o") == 0) {
                        strncpy(file->dst_filename, argv[++i], FILENAME_SIZE - 1);
                } else if (strcmp(argv[i], "-p") == 0) {
                        params->ignore_punc = false;
                } else if (strcmp(argv[i], "-r") == 0) {
                        params->reverse_comp = true;
                } else if (strcmp(argv[i], "-s") == 0) {
                        i++;
                        if (strcmp(argv[i], "--no-sort") == 0) {
                                params->sort_type = NO_SORT;
                        } else if (strcmp(argv[i], "--bubble") == 0) {
                                params->sort_type = BUBBLE_SORT;
                        }
                        else if (strcmp(argv[i], "--quicksort") == 0) {
                                params->sort_type = QUICK_SORT;
                        }
                        else if (strcmp(argv[i], "--qsort") == 0) {
                                params->sort_type = Q_SORT;
                        }
                        else {
                                fprintf(stderr, "Error: Wrong sorting options.\n");
                                return ERR_SORT_OPT;
                        }
                } else if (strcmp(argv[i], "-v") == 0) {
                        params->verbose = true;
                } else {
                        fprintf(stderr, "Error: Wrong parameters.\n");
                        return ERR_PARAMS;
                }
        }

        return ERR_NO_ERR;
}

void print_help()
{
        printf("********* COMMANDS *********\n"
               "-i: enter input file(e.g. -i input.txt)\n"
               "-o: enter output file\n"
               "-h: open manual\n"
               "-s: choose type of sorting\n"
               "-p: sort text including all punctuation characters\n"
               "-r: sort strings from the end of the string to the beginning\n"
               "-v: verbose mode\n"
               "\n"
               "********* SORTING TYPES *********\n"
               "--no-sort: sorting is not executed\n" 
               "--bubble: bubble sort\n"
               "--quicksort: quicksort\n"
               "--qsort: standart C qsort() function\n"
               "\n"
               "********* EXAMPLE *********\n"
               "./onegin -i Romeo_and_Juliet.txt -o sorted_text.txt -r -s --bubble\n"
               "\n"
               "Program will read text from Romeo_and_Juliet.txt, sort it\n"
               "using bubble sort from the end of lines and print input to\n"
               "sorted_text.txt file.\n");
}

