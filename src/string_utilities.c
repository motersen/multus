#include "string_utilities.h"
#include <stdlib.h>
#include <string.h>

tok_array* tok_array_new(char* instring, char const* delimiters)
{
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

void tok_array_free(tok_array* tok_in)
{
    if(tok_in == NULL)
        return;
    free(tok_in->base_string);
    free(tok_in->elements);
    free(tok_in);
}
