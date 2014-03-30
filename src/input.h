#ifndef INPUT_H
#define INPUT_H
#include <stdio.h>

/* Open the src for reading 
 * If src is '-' or NULL, stdin is used for input.
 * Otherwise src is assumed to be the path to a file.
 * If the source could be opened, 0 is returned.
 * If the file could not be opened, an W_LOG_ERROR is
 * printed and -1 is returned.
 * If input_open was called before, it also closes the
 * previous source.
 * */
int input_open(char* src);

/* Receive a pointer to the opened source */
FILE* input_stream(void);

/* Close the opened source */
int input_close(void);
#endif
