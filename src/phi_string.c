#include "phi_string.h"


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
    self->mem_size = sizeof(char) * strlen(self->v) + strlen(other.v);
    self->v = (char*) malloc(self->mem_size);
    sprintf(self->v, "%s%s", self_value, other.v);
}

void String_appendc(String* self, char ch) 
{
    char* ch_p = &ch;
    String_append(self, ch_p);
}

void String_append(String* self, char* other) 
{
    String_appends(self, String_init(other));
}
