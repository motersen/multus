#include <stdio.h>
#include <stdarg.h>
#include "output.h"
#include "options.h"
#include "multus.h"

static int loglevel_match(int minll)
{
    int ll = (flag_get(M_FLAG_VERBOSE) == flag_get(M_FLAG_QUIET))
            ? M_LOG_NORMAL
            : flag_get(M_FLAG_VERBOSE) ? M_LOG_VERBOSE
                                       : M_LOG_ERROR;
    return minll >= ll;
}

static int say_va(int minll,
                  FILE* stream,
                  char* format,
                  va_list vars)
{
    return loglevel_match(minll) ? vfprintf(stream, format, vars)
                                 : 0;
}

int say(int minll, char* format, ...)
{
    int status;
    va_list vars;
    va_start(vars, format);
    status = say_va(minll, stdout, format, vars);
    va_end(vars);
    return status;
}

int say_stream(int minll, FILE* stream, char* format, ...)
{
    int status;
    va_list vars;
    va_start(vars, format);
    status = say_va(minll, stream, format, vars);
    va_end(vars);
    return status;
}

static void hash_stat(GHashTable* hash)
{
    say(M_LOG_NORMAL, "Total:     %8lu tokens\n",
            values_sum(hash));
    if(!flag_get(M_FLAG_CASEFOLD)) {
        say(M_LOG_NORMAL, "Different: %8u individual tokens\n",
                g_hash_table_size(hash)); 
        fold_hash_table(&hash);
    }
    say(M_LOG_NORMAL, "Folds to:  %8u not equally casefolding tokens\n",
                      g_hash_table_size(hash));
}

void output_table(GHashTable* hash)
{
    if(flag_get(M_FLAG_STAT))
        hash_stat(hash);
    else
        g_hash_table_foreach(hash, print_set, NULL);
}

int help(void)
{
return say(M_LOG_NORMAL,
            "wordcount [OPTIONS] [INPUT..]\n"
            "OPTIONS:\n"
            "\t-h --help\n"
            "\t        Display this Help\n"
            "\t-v --verbose\n"
            "\t        Print more information\n"
            "\t-q --quiet\n"
            "\t        Print only errors.\n"       
            "\t-i --ignore-case\n"
            "\t        Ignore casing by fully folding all according to Unicode.\n"
            "\t-s --stat\n"
            "\t        Print statistics about the input.\n"
            "\n"
            "INPUT may be sources that will be evaluated. Stdin is represented by\n"
            "\'-\', everything else is treated as a path to a file.\n"
            "If INPUT is omitted, stdin is evaluated\n"
            );
}
