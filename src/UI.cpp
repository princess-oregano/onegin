#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "UI.h"
#include "sort.h"

// Prints help message.
static void print_help()
{
        printf(
"     \\`*-.                      \n"
"      )  _`-.                    \n"
"     .  : `. .                   \n"
"     : _   '  \\                 \n"
"     ; *` _.   `*-._             \n"
"     `-.-'          `-.          \n"
"       ;       `       `.        \n"
"       :.       .        \\      \n"
"       . \\  .   :   .-'   .     \n"
"       '  `+.;  ;  '      :      \n"
"       :  '  |    ;       ;-.    \n"
"       ; '   : :`-:     _.`* ;   \n"
"    .*' /  .*' ; .*`- +'  `*'    \n"
"    `*-*   `*-*  `*-*'           \n"
"\n"
"************ COMMANDS ************\n"
"  -i, --input       enter input file(e.g. -i input.txt)\n"
"  -o, --output      enter output file\n"
"  -h, --help        print this help and close the program\n"
"  -s, --sort        choose type of sorting\n"
"  -p, --punc        sort text including all punctuation characters\n"
"  -r, --reverse     sort strings from the ends of the strings\n"
"  -v, --verbose     verbose mode\n"
"\n"
"********* SORTING TYPES *********\n"
"  no-sort           sorting is not executed\n"
"  bubble            bubble sort\n"
"  quicksort         quicksort\n"
"  qsort             standart C qsort() function\n"
"\n"
"********* EXAMPLE *********\n"
"./onegin -i Romeo_and_Juliet.txt -o sorted_text.txt -r -s bubble\n"
"\n"
"Program will read text from Romeo_and_Juliet.txt, sort it\n"
"using bubble sort from the end of lines and print input to\n"
"sorted_text.txt file.\n");
}

int get_file(char *filename, file_t *file, const char *mode)
{
        if ((file->file_ptr = fopen(filename, mode)) == nullptr) {
                fprintf(stderr, "Error: Couldn't open %s.\n", filename);

                return ERR_OPEN_FILE;
        }

        if (stat(filename, &file->file_stats) != 0) {
                fprintf(stderr, "Error: Coudn't get stats of %s.\n", filename);
                return ERR_STATS;
        }

        return ERR_NO_ERR;
}

int verbose_msg(bool verbose, const char *format, ...)
{
        if (!verbose)
                return 0;

        va_list args;
        va_start(args, format);
        fprintf(stderr, "VERBOSE: ");
        int ret = vfprintf(stderr, format, args);
        va_end(args);

        return ret;
}

int process_args(int argc, char *argv[], params_t *params)
{
        if ((argc == 2) && ((strcmp(argv[1], "-h") == 0)
                         || (strcmp(argv[1], "--help") == 0))) {
                print_help();
                params->help = true;
                return ERR_NO_ERR;
        }

        for (int i = 1; i < argc; i++) {
                if ((strcmp(argv[i], "-i") == 0) ||
                    (strcmp(argv[i], "--input") == 0)) {
                        params->src_filename = argv[++i];
                } else if ((strcmp(argv[i], "-o") == 0) ||
                           (strcmp(argv[i], "--output") == 0)) {
                        params->dst_filename = argv[++i];
                } else if ((strcmp(argv[i], "-p") == 0) ||
                           (strcmp(argv[i], "--punc") == 0)) {
                        params->ignore_punc = false;
                } else if ((strcmp(argv[i], "-r") == 0) ||
                           (strcmp(argv[i], "--reverse") == 0)) {
                        params->reverse_comp = true;
                } else if ((strcmp(argv[i], "-s") == 0) ||
                           (strcmp(argv[i], "--sort") == 0)) {
                        i++;
                        if (strcmp(argv[i], "no-sort") == 0) {
                                params->sort_type = NO_SORT;
                        } else if (strcmp(argv[i], "bubble") == 0) {
                                params->sort_type = BUBBLE_SORT;
                        }
                        else if (strcmp(argv[i], "quicksort") == 0) {
                                params->sort_type = QUICK_SORT;
                        }
                        else if (strcmp(argv[i], "qsort") == 0) {
                                params->sort_type = Q_SORT;
                        }
                        else {
                                fprintf(stderr, "Error: Wrong sorting options.\n");
                                return ERR_SORT_OPT;
                        }
                } else if ((strcmp(argv[i], "-v") == 0) ||
                           (strcmp(argv[i], "--verbose") == 0)) {
                        params->verbose = true;
                } else {
                        fprintf(stderr, "Error: Wrong parameters.\n");
                        return ERR_PARAMS;
                }
        }

        return ERR_NO_ERR;
}

