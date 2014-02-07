#include <stdio.h>

int print_verbose(char* msg, int opt)
{
    return opt ? puts(msg) : 0;
}

int help()
{
return printf("wordcount [options] <input>\n"
              "options:\n"
              "\t-h --help\n"
              "\t\tDisplay this Help\n"
              "\t-v --verbose\n"
              "\t\tPrint information about operations\n"
              "input:\n"
              "\tThe Input to be analyzed\n"
              "\tValues:\n"
              "\t\tPath to a file to be processed\n"
              "\t\t'-' or no argument (or pipes) to use stdin\n"
       );
}
