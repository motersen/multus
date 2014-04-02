#include "options.h"
#include <glib.h>
#include "input.h"
#include "output.h"
#include "string_utilities.h"
#include "wordcount.h"

int main(int argc, char* argv[])
{
    if(parse_options(argc, argv))
        return -1;
    GHashTable* hash = new_wordcount_hash();
    if(!hash)
        say_stream(W_LOG_ERROR, stderr, "Could not allocate table\n");
    char* delimiters = " \n\t\r\"`~!?@#$%^&*()<>»«{}[]_-+=|\\;:,./";
    hash_streams(hash, input_streams(), delimiters);
    input_close();
    g_hash_table_foreach(hash, print_set, NULL);
    g_hash_table_destroy(hash);
    return 0;
}
