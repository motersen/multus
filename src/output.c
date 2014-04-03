#include <stdio.h>
#include <stdarg.h>
#include "output.h"
#include "options.h"

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
            "\n"
            "INPUT may be sources that will be evaluated. Stdin is represented by\n"
            "\'-\', everything else is treated as a path to a file.\n"
            "If INPUT is omitted, stdin is evaluated\n"
            );
}
