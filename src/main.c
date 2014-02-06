#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "options.h"
#include <glib.h>
#include "output.h"
#include "string_utilities.h"
#include "wordcount.h"

int main(int argc, char* argv[]) {
    if(argc<2) {
        help();
        return -1;
    }
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
    if(optind>=argc) {
        help();
        fprintf(stderr,"No input");
        return -1;
    }
    options.file = strdup(argv[optind]);
    print_verbose("Reading File...", options.verbose);
    char* input = string_from_file(options.file);
    if(!input)
        return -1;
    char* delimiters = " \n\t\r\"`~!?@#$%^&*()<>»«{}[]_-+=|\\;:,./";
    print_verbose("Parsing File...", options.verbose);
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
    free(options.file);
    return 0;
}
