#ifndef output
#define output
int say(unsigned int minll, char* format, ...);
int say_stream(unsigned int minll, FILE* stream, char* format, ...);

int help(void);
#endif
