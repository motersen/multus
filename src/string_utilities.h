#ifndef String_Utils
#define String_Utils
#include <string.h>
#include <stdio.h>

typedef struct tok_array {
    char** elements;
    char* base_string;
    unsigned int length;
} tok_array;

char* string_from_stream(FILE* stream);

tok_array* tok_array_new(char* instring, char const* delimiters);
void tok_array_free(tok_array* tok_in);
#endif
