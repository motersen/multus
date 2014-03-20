#include <stdio.h>
#include <stdarg.h>
#include "options.h"

static int say_va(unsigned int minll,
                  FILE* stream,
                  char* format,
                  va_list vars)
{
    return (options.loglevel <= minll) ? vfprintf(stream, format, vars)
                                       : 0;
}

int say(unsigned int minll, char* format, ...)
{
    int status;
    va_list vars;
    va_start(vars, format);
    status = say_va(minll, stdout, format, vars);
    va_end(vars);
    return status;
}

int say_stream(unsigned int minll, FILE* stream, char* format, ...)
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
return printf(  "wordcount [OPTIONS] [INPUT]\n"
                "OPTIONS:\n"
                "\t  -h --help\n"
                "\t\t    Display this Help\n"
                "\t  -v --verbose\n"
                "\t\t    Print status information\n"
                "\n"
                "If INPUT is passed, it will be tried to read from a file with the name.\n"
                "Otherwise, or if INPUT is '-', input will be read from stdin.\n");
}
