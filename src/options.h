#ifndef Options
#define Options
#include <stdio.h>
#include <getopt.h>

typedef struct {
    unsigned int verbose: 1;
    FILE* input;
    int optindex;
    int iterator;
} optionstruct;
#endif
