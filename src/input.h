#ifndef INPUT_H
#define INPUT_H
#include <stdio.h>

/* Open the sources for reading 
 * If an element is '-', stdin is used for input.
 * Otherwise it is assumed to be the path to a file.
 * If input_open was called before, it also closes the
 * previous sources.
 * */
void input_open(char** src);

/* Receive a pointer to the opened sources */
FILE** input_streams(void);

/* Close the opened sources */
void input_close(void);
#endif
