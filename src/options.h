#ifndef Options
#define Options
#include <getopt.h>

typedef struct {
    unsigned int verbose: 1;
    char* file;
    int optindex;
    int iterator;
} optionstruct;
#endif
