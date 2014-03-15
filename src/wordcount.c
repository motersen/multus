#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include "string_utilities.h"
#include "wordcount.h"

void hash_word(char* word, GHashTable* hash) {
    count_s* value = g_hash_table_lookup(hash, word);
    if(!value) {
        value = malloc(sizeof(count_s));
        *value = (count_s){};
        char* key = strdup(word);
        if(!key) {
            fprintf(stderr, "Could not allocate memory to store \"%s\"\n", word);
            return;
        }
        g_hash_table_insert(hash, key, value);
    }
    value->count++;
}

void print_set(gpointer key_in, gpointer val_in, gpointer ignored) {
    char const* key = key_in;
    count_s const* val = val_in;
    printf("%d\t%s\n", val->count, key);
}

GHashTable* new_wordcount_hash() {
    return g_hash_table_new_full(g_str_hash, g_str_equal, key_free, val_free);
}

void key_free(gpointer freekey) {
    char* key = freekey;
    free(key);
}

void val_free(gpointer freeval) {
    count_s* val = freeval;
    free(val);
}
