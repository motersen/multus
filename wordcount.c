#include <glib.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "string_utilities.h"
#include "wordcount.h"

void hash_word(char* word, GHashTable* hash) {
    count_s* value = g_hash_table_lookup(hash, &word);
    if(!value) {
        value = malloc(sizeof(count_s));
        *value = (count_s){.count = 1};
        char* key;
        if(asprintf(&key, word) == -1) {
            fprintf(stderr, "Konnte String »%s« nicht in Hash-Tabelle eintragen", word);
            return;
        }
        g_hash_table_insert(hash, &key, value);
        free(key);
    } else {
        value->count++;
    }
}

void print_set(void* key_in, void* val_in, void* ignored) {
    char const** key = key_in;
    count_s const* val = val_in;
    printf("%s\t%d\n", *key, val->count);
}

GHashTable* new_wordcount_hash() {
    return g_hash_table_new(g_str_hash, g_str_equal);
}
