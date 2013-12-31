#include <glib.h>
#include <string.h>
#include "string_utilities.h"
#include <stdio.h>
#include <stdlib.h> //abort

char* string_from_file(char const* filename) {
    char* out;
    GError* e = NULL;
    GIOChannel* f = g_io_channel_new_file(filename, "r", &e);
    if(!f) {
        fprintf(stdout, "Konnte Datei »%s« nicht öffnen.\n", filename);
        return NULL;
    }
    if(g_io_channel_read_to_end(f, &out, NULL, &e) != G_IO_STATUS_NORMAL) {
        fprintf(stdout, "Datei »%s« gefunden, aber nicht einlesbar.\n", filename);
        return NULL;
    }
    return out;
}

tok_array* tok_array_new(char* instring, char const* delimiters) {
    tok_array* out = malloc(sizeof(tok_array));
    *out = (tok_array){.base_string=instring};
    char* scratch = NULL;
    char* txt = strtok_r(instring, delimiters, &scratch);
    if(!txt)
        return NULL;
    while(txt) {
        out->elements = realloc(out->elements, sizeof(char*)*++(out->length));
        out->elements[out->length-1] = txt;
        txt = strtok_r(NULL, delimiters, &scratch);
    }
    return out;
}

void tok_array_free(tok_array* tok_in) {
    if(tok_in == NULL)
        return;
    free(tok_in->base_string);
    free(tok_in->elements);
    free(tok_in);
}
