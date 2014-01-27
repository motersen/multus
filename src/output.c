#include <stdio.h>

int print_verbose(char* msg, int opt)
{
    return opt ? puts(msg) : 0;
}

int help()
{
return printf("wordcount [options] [file]\n"
              "required:\n"
              "    -f --file <filename>\n"
              "        Specifies the path to the File to be read\n"
              "optional:\n"
              "    -h --help\n"
              "        Display this Help\n"
              "    -v --verbose\n"
              "        Print information about operations\n");
}
