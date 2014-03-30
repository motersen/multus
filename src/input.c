#include <stdio.h>
#include <string.h>
#include "input.h"
#include "output.h"

static FILE* input = NULL;

int input_open(char* src)
{
    if(input)
        input_close();
    if(!src || !strcmp(src, "-")) {
        say(W_LOG_VERBOSE, "Input is read from STDIN\n");
        input = stdin;
        return 0;
    }
    say(W_LOG_VERBOSE, "Input is read from File\n");
    input = fopen(src, "r");
    if(!input) {
        say_stream(W_LOG_ERROR,
                   stderr, "Could not open file %s\n", src);
        return -1;
    }
    return 0;
}


FILE* input_stream(void)
{
    return input;
}

int input_close(void) {
    if(input != stdin)
        return fclose(input);
    return 0;
}
