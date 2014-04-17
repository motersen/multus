#include "utf8.h"
#include "utf_data.h"
#include "output.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* Determine how many continuous high-order 1s appear before the first 0
 * in the byte. For multi-byte sequences, this is the number of bytes
 * that belong to the codepoint.
 * This implementation uses a function:
 * f(x) = floor(-log2(256-x)+8)
 * where x is an 8-bit sequence and f(x) is the number of 1s from MSB
 * preceding the first 0.
 */
static int high_set_bits(byte enc)
{
    return (int) floor(-log(256 - (double) enc)/log(2)+8);
}

/* Determine how many bits the prefix takes up */
static int prefix_length(byte enc)
{
    return high_set_bits(enc) + 1;
}

/* Determine how many bits the codepoint part takes up */
static int codepoint_data_length(byte enc)
{
    return 8 - prefix_length(enc);
}

static int is_continuation_byte(byte enc)
{
    return high_set_bits(enc) == 1;
}

/* Determine how many bytes the glyph takes
 * up as declared in this bytes prefix.
 */
static int multibyte_length(byte enc)
{
    return (enc <= 127) ? 1
                         : high_set_bits(enc);
}

static int is_ascii(byte enc)
{
    return high_set_bits(enc) == 0;
}

static int valid_prefix(byte enc)
{
    return (enc >= 248) ? 0 : 1;
}

/* Return a byte with length continuous high-order bits set.
 * This implementation uses the inverse of the function used in
 * multibyte_length:
 * f(x) = 256-2^(8-x)
 * Since this function is not limited to UTF-8 compliant prefixes
 * it should not be used directly.
 */
static byte multibyte_prefix(int bits)
{
    return (int) 256-pow(2, (8-bits));
}

static byte continuation_byte_prefix(void)
{
    return multibyte_prefix(1);
}

/* Return the prefix for an encoded
 * sequence of length bytes.
 */
static byte leading_byte_prefix(int length)
{
    return  (length == 1) ? multibyte_prefix(0)
          : multibyte_prefix(length);
}

/* Return the codepoint data part of the encoded byte.
 * This is the byte without it's prefix.
 */
static byte codepoint_data(byte enc)
{
    return enc & (255 >> prefix_length(enc));
}

/* Determine the number of bytes needed to represent the
 * codepoint dec encoded in UTF-8
 */
static int codepoint_byte_length(codepoint dec)
{
    if(dec > 1114111UL) {
        say_stream(M_LOG_ERROR, stderr, "U+%04X is not a valid Codepoint\n", dec);
        return -1;
    }
    return  (dec <= 127U)      ? 1
          : (dec <= 2047U)     ? 2
          : (dec <= 65535U)    ? 3
          :                      4;
}

/* Encode a single codepoint in UTF-8
 * Since each continuation byte in UTF-8 holds 6 bits of the codepoint
 * value, the individual bytes are formed by shifting the codepoint by
 * a multiple of 6 and adding the respective prefix (header or continuation)
 */
static byte* encode_codepoint(codepoint dec)
{
    int length = codepoint_byte_length(dec);
    if(length == -1)
        return NULL;
    byte* enc = malloc(sizeof(byte) * length);
    enc[0] = leading_byte_prefix(length)
             + (dec >> (6 * (length - 1)));
    for(int i=1;i<length;++i)
        enc[i] = continuation_byte_prefix()
                 + (dec >> 6 * (length - (i+1)) & 63);
    return enc;
}

/* Decode a single UTF-8 encoded glyph */
static codepoint decode_codepoint(byte* enc)
{
    if(is_ascii(*enc))
        return (codepoint) *enc;
    if(!valid_prefix(*enc))
        return CODEPOINT_ERROR;
    int length = multibyte_length(*enc);
    codepoint dec = 0;
    for(int i=0;i<length;++i) {
        if(i>0 && !is_continuation_byte(enc[i]))
                return CODEPOINT_ERROR;
        dec = (dec << codepoint_data_length(enc[i]))
              + codepoint_data(enc[i]);
    }
    return dec;
}

/* Return a pointer to a dynamically allocated sequence
 * of codepoints that is a duplicate of the codepoints
 * at off until the first occurrence of CODEPOINT_SENTINEL.
 */
static codepoint* duplicate_codepoints(codepoint* off)
{
    codepoint *out = NULL;
    int length = 0;
    for(codepoint* it=off;*it!=CODEPOINT_SENTINEL;++it) {
        out = realloc(out, sizeof(codepoint) * ++length);
        out[length-1] = *it;
    }
    out = realloc(out, sizeof(codepoint) * (length + 1));
    out[length] = CODEPOINT_SENTINEL;
    return out;
}

static codepoint* lookup_fold(codepoint code)
{
    for(int i=0;codes[i]!=CODEPOINT_SENTINEL;++i)
        if(codes[i] == code)
            return duplicate_codepoints(mappings[i]);
    return duplicate_codepoints((codepoint[]) {code, CODEPOINT_SENTINEL});
}

/* Decode the NULL-terminated string from UTF-8. */
codepoint* utf8_decode(byte* enc)
{
    codepoint *out=NULL, buf;
    int length=0;
    byte* offset=enc;
    while(*offset) {
        out = realloc(out, sizeof(codepoint) * ++length);
        buf = decode_codepoint(offset);
        if(buf == CODEPOINT_ERROR) {
            free(out);
            return NULL;
        }
        out[length-1] = buf;
        offset += multibyte_length(*offset);
    }
    out = realloc(out, sizeof(codepoint) * (length + 1));
    out[length] = CODEPOINT_SENTINEL;
    return out;
}

/* Encode the CODEPOINT_SENTINEL-terminated sequence in UTF-8. */
byte* utf8_encode(codepoint* dec)
{
    byte *out=NULL, *buf=NULL;
    int length=0, buflen=0;
    codepoint* offset=dec;
    while(*offset!=CODEPOINT_SENTINEL) {
        buf = encode_codepoint(*offset);
        if(!buf) {
            free(out);
            return NULL;
        }
        buflen = multibyte_length(*buf);
        out = realloc(out, sizeof(byte) * (buflen + length));
        memcpy(out+length, buf, sizeof(byte) * buflen); 
        length += buflen;
        free(buf);
        ++offset;
    }
    out = realloc(out, sizeof(byte) * (length + 1));
    out[length] = '\0';
    return out;
}

/* Fold all glyphs in unfold to their full mapping. */
byte* utf8_casefold(byte* enc)
{
    codepoint* dec = utf8_decode(enc);
    if(!dec)
        return NULL;
    int length=0;
    codepoint *offset=dec, *buf=NULL, *codes=NULL;
    while(*offset!=CODEPOINT_SENTINEL) {
        buf = lookup_fold(*offset);
        for(codepoint* it=buf;*it!=CODEPOINT_SENTINEL;++it) {
            codes = realloc(codes, sizeof(codepoint) * ++length);
            codes[length-1] = *it;
        }
        free(buf);
        ++offset;
    }
    free(dec);
    codes = realloc(codes, sizeof(codepoint) * (length + 1));
    codes[length] = CODEPOINT_SENTINEL;
    byte* out = utf8_encode(codes);
    free(codes);
    return out;
}
