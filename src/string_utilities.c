#include "string_utilities.h"
#include <stdio.h>
#include <stdlib.h> //abort

char* string_from_stream(FILE* stream) {
    char** lines = NULL;
    int length=0;
    char* buf = NULL;
    size_t bufsiz = 0;
    ssize_t buflen=0;
    ssize_t chars=0;
    while((buflen = getline(&buf, &bufsiz, stream)) != -1) {
        lines = realloc(lines, sizeof(char*) * ++length);
        lines[length-1] = strdup(buf);
        chars += buflen;
    }
    free(buf);
    lines = realloc(lines, sizeof(char*) * ++length);
    lines[length-1] = NULL;
    char* out = malloc(chars+2);
    *out = 0;
    for(char** it=lines;*it;++it) {
        out = strcat(out, *it);
        free(*it);
    }
    free(lines);
    return out;
}

tok_array* tok_array_new(char* instring, char const* delimiters) {
    tok_array* out = malloc(sizeof(tok_array));
    *out = (tok_array){.base_string=instring};
    char* scratch = NULL;
    char* txt = strtok_r(instring, delimiters, &scratch);
    if(!txt) {
        free(out);
        return NULL;
    }
    while(txt) {
        out->elements = realloc(out->elements, sizeof(char*)*++(out->length));
        out->elements[out->length-1] = txt;
        txt = strtok_r(NULL, delimiters, &scratch);
    }
    out->elements = realloc(out->elements, sizeof(char*)*(out->length+1));
    out->elements[out->length] = NULL;
    return out;
}

void tok_array_free(tok_array* tok_in) {
    if(tok_in == NULL)
        return;
    free(tok_in->base_string);
    free(tok_in->elements);
    free(tok_in);
}
