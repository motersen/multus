#ifndef UTF8_H
#define UTF8_H

#define CODEPOINT_ERROR 0x110000
#define CODEPOINT_SENTINEL 0

typedef unsigned long int codepoint;
typedef unsigned char byte;

/* Fold all glyphs in unfold to their full mapping.
 * enc must be NULL-terminated.
 * Return value is NULL-terminated
 * and must be freed.
 */
byte* utf8_casefold(byte* enc);

/* Decode the string from UTF-8.
 * enc must be NULL-terminated.
 * Return value is terminated by
 * CODEPOINT_SENTINEL and must be freed.
 */
codepoint* utf8_decode(byte* enc);

/* Encode all codepoints in UTF-8.
 * dec must be terminated by CODEPOINT_SENTINEL.
 * Return value is NULL-terminated
 * and must be freed.
 */
byte* utf8_encode(codepoint* dec);

#endif
