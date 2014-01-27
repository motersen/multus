#ifndef WordCount
#define WordCount
#include <glib.h>

typedef struct {
    unsigned int count;
} count_s;

void hash_word(char* word, GHashTable* hash);
void print_set(void* key_in, void* val_in, void* ignored);
GHashTable* new_wordcount_hash();
void key_free(gpointer key);
void val_free(gpointer val);
#endif
