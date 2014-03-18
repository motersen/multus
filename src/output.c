#include <stdio.h>

int print_verbose(char* msg, int opt)
{
    return opt ? puts(msg) : 0;
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
