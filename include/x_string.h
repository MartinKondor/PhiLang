#ifndef _STRING_H_INCLUDED_
#define _STRING_H_INCLUDED_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    /**
     * Example use:

    String str = String_init("Allocate me.");
    String_append(&str, " Appended.");
    String_append(&str, " Appended 2.");

    printf("%s\n", str.v);  // Allocate me. Appended. Appended 2.

    free(str.v);
    */
    char* v;
    unsigned int mem_size;
} String;

String String_init(char* characters);

/**
 * Removes the contents of the given string.
 */
void String_clear(String* self);

/**
 * Appends a string to an other.
 */
void String_appends(String* self, String other);

/**
 * Appends a char to a string.
 */
void String_appendc(String* self, char ch);

/**
 * Appends a char array to a string.
 */
void String_append(String* self, char* other);

#endif
