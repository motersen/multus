#ifndef Options
#define Options
#include <stdio.h>
#include <getopt.h>

#define W_FLAG_VERBOSE  0
#define W_FLAG_QUIET    1

/* Evaluate the first argc options given in argv */
int parse_options(int argc, char* argv[]);

/* Returns 1 if the requested flag (as defined above)
 * is set and 0 otherwise.
 */
int flag_get(unsigned int flag);

/* Set the requested flag */
void flag_set(unsigned int flag);

/* Unset the requested flag */
void flag_unset(unsigned int flag);
#endif
