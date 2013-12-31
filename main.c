#include <stdio.h>
#include <glib.h>
#include "string_utilities.h"
#include "wordcount.h"

int main(int argc, char* argv[]) {
    if(argc<2) {
        fprintf(stderr, "Kein Dateiname angegeben. Verwendung:\n%s [textdatei]", *argv);
        return -1;
    }
    puts("Reading File...");
    char* input = string_from_file(argv[1]);
    if(!input)
        return -1;
    char* delimiters = " \n\t\r\"`~!?@#$%^&*()<>»«{}[]_-+=|\\;:,./";
    puts("Parsing File...");
    tok_array* words = tok_array_new(input, delimiters);
    GHashTable* hash = new_wordcount_hash();
    puts("Counting Words...");
    for(unsigned int i = 0;i<words->length;++i)
        hash_word(words->elements[i], hash);
    puts("Printing Words...");
    g_hash_table_foreach(hash, print_set, NULL);
    puts("Destroying the Table...");
    g_hash_table_destroy(hash);
    return 0;
}
