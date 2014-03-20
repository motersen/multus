#ifndef Options
#define Options
#include <stdio.h>
#include <getopt.h>

#define W_LOG_VERBOSE 0
#define W_LOG_NORMAL  1
#define W_LOG_QUIET   2

typedef struct {
    unsigned int loglevel: 2;
    FILE* input;
    int optindex;
    int iterator;
} optionstruct;

extern optionstruct options;
#endif
