#ifndef output
#define output

#define M_LOG_VERBOSE   0
#define M_LOG_NORMAL    1
#define M_LOG_ERROR     2

int say(int minll, char* format, ...);
int say_stream(int minll, FILE* stream, char* format, ...);

int help(void);
#endif
