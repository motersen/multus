#ifndef output
#define output
#include <stdio.h>
#include <glib.h>

#define M_LOG_VERBOSE   0
#define M_LOG_NORMAL    1
#define M_LOG_ERROR     2

int say(int minll, char* format, ...);
int say_stream(int minll, FILE* stream, char* format, ...);

void output_table(GHashTable* hash);

int help(void);
#endif
