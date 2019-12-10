#include "phi_variable_list.h"


PhiVariableList PhiVariableList_init()
{
    PhiVariableList list;
    list.length = 0;
    return list;
}

void PhiVariableList_append(PhiVariableList* list, PhiVariable value)
{
    PhiVariable* backup_storage = list->storage;
    list->storage = (PhiVariable*) malloc(++list->length * sizeof(PhiVariable));

    if (!list->storage) 
    {
        printf("PhiVariableList: error with allocating memory.\n");
        exit(1);
    }

    for (unsigned int i = 0; i < list->length - 1; i++) 
    {
        list->storage[i] = backup_storage[i];
    }

    list->storage[list->length - 1] = value;
}

PhiVariable* PhiVariableList_at(PhiVariableList list, unsigned int index)
{
    if (index > list.length - 1)
    {
        printf("PhiVariableList: the given index (%u) is too big.\n", index);
        exit(1);
    }
    return &list.storage[index];
}
