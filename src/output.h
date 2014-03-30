#ifndef output
#define output

#define W_LOG_VERBOSE   0
#define W_LOG_NORMAL    1
#define W_LOG_ERROR     2

int say(int minll, char* format, ...);
int say_stream(int minll, FILE* stream, char* format, ...);

int help(void);
#endif
