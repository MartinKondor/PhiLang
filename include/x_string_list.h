#ifndef _STRING_LIST_H_INCLUDED_
#define _STRING_LIST_H_INCLUDED_

#include "x_string.h"


typedef struct
{
    String* storage;
    unsigned int length;
} StringList;


StringList StringList_init();
void StringList_append(StringList* list, String value);
String* StringList_at(StringList list, unsigned int index);

#endif
