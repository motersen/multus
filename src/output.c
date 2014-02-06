#include <stdio.h>

int print_verbose(char* msg, int opt)
{
    return opt ? puts(msg) : 0;
}

int help()
{
return printf("wordcount [options] <input>\n"
              "options:\n"
              "    -h --help\n"
              "        Display this Help\n"
              "    -v --verbose\n"
              "        Print information about operations\n"
              "input:\n"
              "    The path to the file to be analyzed\n"
       );
}
