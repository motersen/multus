#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "options.h"
#include <glib.h>
#include "output.h"
#include "string_utilities.h"
#include "wordcount.h"

int main(int argc, char* argv[]) {
    optionstruct options = {};
    static struct option long_options[] = {
        {"help",    no_argument,       NULL, 'h'},
        {"verbose", no_argument,       NULL, 'v'},
        {NULL,      0,                 NULL, 0}
    };
    while((options.iterator = getopt_long(argc, argv, "hv", long_options, &options.optindex)) != -1) {
        switch(options.iterator) {
            case 'h':
                help();
                return 0;
            case 'v':
                options.verbose = 1;
                break;
            default:
                help();
                fprintf(stderr, "Invalid Option: %s\n", optarg);
                return -1;
        }
    }
    if(optind>=argc || !strcmp(argv[optind], "-")) {
        options.input = stdin;
    } else {
        options.input = fopen(argv[optind], "r");
        if(options.input == NULL) {
            fprintf(stderr, "Failed to read from »%s«\n", argv[optind]);
            return -1;
        }
    }
    print_verbose("Reading Input...", options.verbose);
    char* input = string_from_stream(options.input);
    if(options.input != stdin)
        fclose(options.input);
    if(!input)
        return -1;
    char* delimiters = " \n\t\r\"`~!?@#$%^&*()<>»«{}[]_-+=|\\;:,./";
    print_verbose("Parsing Input...", options.verbose);
    tok_array* words = tok_array_new(input, delimiters);
    GHashTable* hash = new_wordcount_hash();
    print_verbose("Counting Words...", options.verbose);
    for(char** ptr = words->elements;*ptr;++ptr)
        hash_word(*ptr, hash);
    print_verbose("Printing Words...", options.verbose);
    g_hash_table_foreach(hash, print_set, NULL);
    print_verbose("Destroying the Table...", options.verbose);
    g_hash_table_destroy(hash);
    print_verbose("Freeing Words...", options.verbose);
    tok_array_free(words);
    return 0;
}
