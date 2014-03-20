#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "options.h"
#include <glib.h>
#include "output.h"
#include "string_utilities.h"
#include "wordcount.h"

optionstruct options = {W_LOG_NORMAL, NULL, 0, 0};

int main(int argc, char* argv[])
{
    static struct option long_options[] = {
        {"help",    no_argument,       NULL, 'h'},
        {"verbose", no_argument,       NULL, 'v'},
        {"quiet",   no_argument,       NULL, 'q'},
        {NULL,      0,                 NULL, 0}
    };
    while((options.iterator = getopt_long(argc, argv, "hvq", long_options, &options.optindex)) != -1) {
        switch(options.iterator) {
            case 'h':
                help();
                return 0;
            case 'v':
                options.loglevel = W_LOG_VERBOSE;
                break;
            case 'q':
                options.loglevel = W_LOG_QUIET;
                break;
            default:
                help();
                say_stream(W_LOG_QUIET, stderr, "Invalid Option: %s\n", optarg);
                return -1;
        }
    }
    if(optind>=argc || !strcmp(argv[optind], "-")) {
        options.input = stdin;
        say(W_LOG_VERBOSE, "Input is read from STDIN\n");
    } else {
        say(W_LOG_VERBOSE, "Input is read from File\n");
        options.input = fopen(argv[optind], "r");
        if(options.input == NULL) {
            say_stream(W_LOG_QUIET, stderr, "Failed to read from »%s«\n", argv[optind]);
            return -1;
        }
    }
    GHashTable* hash = new_wordcount_hash();
    if(!hash)
        say_stream(W_LOG_QUIET, stderr, "Could not allocate table\n");
    char* delimiters = " \n\t\r\"`~!?@#$%^&*()<>»«{}[]_-+=|\\;:,./";
    if(options.input == stdin) {
        hash_stream(hash, options.input, delimiters);
    } else {
        char* input = string_from_stream(options.input);
        hash_string(hash, input, delimiters);
        fclose(options.input);
    }
    g_hash_table_foreach(hash, print_set, NULL);
    g_hash_table_destroy(hash);
    return 0;
}
