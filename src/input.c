#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "input.h"
#include "output.h"

static FILE** input = NULL;

static FILE* open_stream(char* src)
{
    FILE* ret = NULL;
    if(!strcmp(src, "-")) {
        say(W_LOG_VERBOSE, "Input is read from STDIN\n");
        ret = stdin;
    } else {
        say(W_LOG_VERBOSE, "Input is read from File %s\n", src);
        ret = fopen(src, "r");
        if(!ret)
            say_stream(W_LOG_ERROR, stderr, "Could not open file %s\n", src);
    }
    return ret;
}

void input_open(char** src)
{
    int size = 0;
    if(input)
        input_close();
    if(!src) {
        say(W_LOG_VERBOSE, "Input is read from STDIN\n");
        input = realloc(input, sizeof(FILE*)*++size);
        input[size-1] = stdin;
        goto addnull;
    }
    char** strit = src;
    FILE*  tmp = NULL;
    while(*strit) {
        tmp = open_stream(*strit);
        if(!tmp)
            goto next;
        input = realloc(input, sizeof(FILE*)*++size);
        input[size-1] = tmp;
next:
        ++strit;
    }
addnull:
    input = realloc(input, sizeof(FILE*)*++size);
    input[size-1] = NULL;
}

FILE** input_streams(void)
{
    return input;
}

void input_close(void)
{
    for(FILE** it=input;*it;++it) {
        if(*it == stdin)
            continue;
        if(fclose(*it))
            say_stream(W_LOG_ERROR, stderr, "Could not close File\n");
    }
    free(input);
}
