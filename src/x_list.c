#include "phi_variable.h"


typedef struct
{
    void* v;
} ListItem;

typedef struct
{
    /**
     * Example:
    List list = List_init();

    PhiVariable var = PhiVariable_init(String_init("test_name"), PhiType_NULL, String_init("test_value"));   
    List_append(&list, var);

    PhiVariable var2 = PhiVariable_init(String_init("test_name_2"), PhiType_NULL, String_init("test_value_2"));
    List_append(&list, var2);   
    */
    ListItem* storage;
    unsigned int length;
} List;

List List_init()
{
    List list;
    list.length = 0;
    return list;
}

void List_append(List* list, void* value) 
{
    ListItem* storage_backup = list->storage;
    list->storage = (ListItem*) malloc(sizeof(ListItem) * ++list->length);

    for (unsigned int i = 0; i < list->length - 1; i++)
    {
        list->storage[i] = storage_backup[i];
    }

    list->storage[list->length - 1].v = value;
}

ListItem List_at(List list, unsigned int index)
{
    return list.storage[index];
}
