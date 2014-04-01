#include <getopt.h>
#include <string.h>
#include "input.h"
#include "options.h"
#include "output.h"

typedef struct {
    unsigned int flags: 2;
} optionstruct;

static optionstruct options;

static struct option long_options[] = {
        {"help",    no_argument,       NULL, 'h'},
        {"verbose", no_argument,       NULL, 'v'},
        {"quiet",   no_argument,       NULL, 'q'},
        {NULL,      0,                 NULL, 0}
};

int parse_options(int argc, char* argv[])
{
    int optiter, optindex=0;
    while((optiter = getopt_long(argc, argv, "hvq", long_options, &optindex)) != -1) {
        switch(optiter) {
        case 'h':
            help();
            break;
        case 'v':
            flag_set(W_FLAG_VERBOSE);
            break;
        case 'q':
            flag_set(W_FLAG_QUIET);
            break;
        default:
            help();
            say_stream(W_LOG_ERROR, stderr, "Invalid Option: %s\n", optarg);
            return -1;
        }
    }
    if(optind>=argc)
        return input_open(NULL);
    else
        return input_open(argv[optind]);
}

/* Mask the bit at the requested position */
static unsigned int bitmask(unsigned int flag)
{
    return 1 << flag;
}

/* Detect if the bit at the requested index in the flag
 * field is set.
 * The flag bits are shifted to the right by the index
 * of the requested flag to get it's value to the LSB.
 * The result is AND-ed with 1 to eliminate all other bits
 * and keep the LSB value. If the flag is set, the value
 * is 1 then, otherwise it is 0.
 */
int flag_get(unsigned int flag)
{
    return ((options.flags >> flag) & 1);
}

/* Set the bit at the requested index in the flag field to 1 */
void flag_set(unsigned int flag)
{
    options.flags |= bitmask(flag);
}

/* Set the bit at the requested index in the flag field to 0 */
void flag_unset(unsigned int flag)
{
    options.flags &= ~bitmask(flag);
}