#include "x_string_list.h"


StringList StringList_init() 
{
    StringList list;
    list.length = 0;
    return list;
}

void StringList_append(StringList* list, String value)
{
    String* backup_storage = list->storage;
    list->storage = (String*) malloc(++list->length * sizeof(String));
    
    for (unsigned int i = 0; i < list->length - 1; i++) 
    {
        list->storage[i] = backup_storage[i];
    }

    list->storage[list->length - 1] = value;
}

String* StringList_at(StringList list, unsigned int index)
{
    if (index > list.length - 1)
    {
        printf("StringList: the given index (%u) is too big.\n", index);
        exit(1);
    }
    return &list.storage[index];
}