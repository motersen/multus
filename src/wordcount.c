#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include "string_utilities.h"
#include "wordcount.h"

void hash_word(char* word, GHashTable* hash)
{
    count_s* value = g_hash_table_lookup(hash, word);
    if(!value) {
        value = malloc(sizeof(count_s));
        *value = (count_s){};
        char* key = strdup(word);
        if(!key) {
            fprintf(stderr, "Could not allocate memory to store \"%s\"\n", word);
            free(value);
            return;
        }
        g_hash_table_insert(hash, key, value);
    }
    value->count++;
}

void hash_string(GHashTable* hash, char* string, char* delims)
{
    tok_array* words = tok_array_new(string, delims);
    if(!words) {
        free(string);
        return;
    }
    for(char** ptr = words->elements;*ptr;++ptr)
        hash_word(*ptr, hash);
    tok_array_free(words);
}

void hash_stream(GHashTable* hash, FILE* stream, char* delims)
{
    char* buf = NULL;
    size_t bufsiz = 0;
    char* tmp = NULL;
    while(getline(&buf, &bufsiz, stream) != -1) {
        tmp = strdup(buf);
        hash_string(hash, tmp, delims);
    } 
    free(buf);
}

static void key_free(gpointer freekey)
{
    char* key = freekey;
    free(key);
}

static void val_free(gpointer freeval)
{
    count_s* val = freeval;
    free(val);
}

void print_set(gpointer key_in, gpointer val_in, gpointer ignored)
{
    char const* key = key_in;
    count_s const* val = val_in;
    printf("%d\t%s\n", val->count, key);
}

GHashTable* new_wordcount_hash(void)
{
    return g_hash_table_new_full(g_str_hash, g_str_equal, key_free, val_free);
}
