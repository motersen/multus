#ifndef WordCount
#define WordCount
#include <glib.h>

typedef struct {
    unsigned int count;
} count_s;

void hash_word(char* word, GHashTable* hash);
void hash_string(GHashTable* hash, char* string, char* delims);
void hash_stream(GHashTable* hash, FILE* stream, char* delims);
void hash_streams(GHashTable* hash, FILE** streams, char* delims);
void print_set(void* key_in, void* val_in, void* ignored);
long unsigned int values_sum(GHashTable* hash);
GHashTable* new_wordcount_hash(void);
GHashTable* fold_hash_table(GHashTable** hash);
#endif
