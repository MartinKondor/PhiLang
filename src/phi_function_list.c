#include "phi_function_list.h"


PhiFunctionList PhiFunctionList_init() 
{
    PhiFunctionList list;
    list.length = 0;
    return list;
}

void PhiFunctionList_append(PhiFunctionList* list, PhiFunction value)
{
    PhiFunction* backup_storage = list->storage;
    list->storage = (PhiFunction*) malloc(++list->length * sizeof(PhiFunction));
    
    if (!list->storage) 
    {
        printf("PhiFunctionList: error with allocating memory.\n");
        exit(1);
    }

    for (unsigned int i = 0; i < list->length - 1; i++) 
    {
        list->storage[i] = backup_storage[i];
    }

    list->storage[list->length - 1] = value;
}

PhiFunction* PhiFunctionList_at(PhiFunctionList list, unsigned int index)
{
    if (index > list.length - 1)
    {
        printf("PhiFunctionList: the given index (%u) is too big.\n", index);
        exit(1);
    }
    return &list.storage[index];
}


