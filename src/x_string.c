#include "x_string.h"


String String_init(char* characters)
{
    String str;
    str.v = characters;
    return str;
}

void String_clear(String* self)
{
    self->v = "";
    self->mem_size = 0;
}

void String_appends(String* self, String other) 
{
    char* self_value = self->v;
    self->mem_size = sizeof(char) * strlen(self->v) + strlen(other.v) + 1;
    self->v = (char*) malloc(self->mem_size);
    // sprintf(self->v, "%s%s", self_value, other.v);
    unsigned int i, vi = 0;

    for (i = 0; i < strlen(self_value); i++, vi++) 
    {
        self->v[vi] = self_value[i];
    }

    for (i = 0; i < strlen(other.v); i++, vi++) 
    {
        self->v[vi] = other.v[i];
    }

    self->v[vi] = '\0';
}

void String_appendc(String* self, char ch) 
{
    char chs[2];
    sprintf(chs, "%c\0", ch);
    String_append(self, chs);
}

void String_append(String* self, char* other) 
{
    String_appends(self, String_init(other));
}
