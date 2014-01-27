#include <stdio.h>
#include <getopt.h>
#include "options.h"
#include <glib.h>
#include "string_utilities.h"
#include "wordcount.h"

int main(int argc, char* argv[]) {
    if(argc<2) {
        fprintf(stderr, "Kein Dateiname angegeben. Verwendung:\n%s [textdatei]", *argv);
        return -1;
    }
    optionstruct options = {};
    static struct option long_options[] = {
        {"verbose", no_argument, NULL, 'v'},
        {"file",    required_argument, NULL, 'f'},
        {NULL, 0, NULL, 0}
    };
    while((options.iterator = getopt_long(argc, argv, "vf:", long_options, &options.optindex)) != -1) {
        switch(options.iterator) {
            case 'v':
                puts("verbose output set");
                options.verbose = 1;
                break;
            case 'f':
                options.file = strdup(optarg);
                break;
            default:
                fprintf(stderr, "Invalid Option: %s\n", optarg);
                return -1;
        }
    }
    puts("Reading File...");
    char* input = string_from_file(options.file);
    if(!input)
        return -1;
    char* delimiters = " \n\t\r\"`~!?@#$%^&*()<>»«{}[]_-+=|\\;:,./";
    puts("Parsing File...");
    tok_array* words = tok_array_new(input, delimiters);
    GHashTable* hash = new_wordcount_hash();
    puts("Counting Words...");
    for(char** ptr = words->elements;*ptr;++ptr)
        hash_word(*ptr, hash);
    if(options.verbose) {
        puts("Printing Words...");
        g_hash_table_foreach(hash, print_set, NULL);
    }
    puts("Destroying the Table...");
    g_hash_table_destroy(hash);
    puts("Freeing Words...");
    tok_array_free(words);
    return 0;
}
