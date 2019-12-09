#ifndef _PHI_VARIABLE_LIST_H_INCLUDED_
#define _PHI_VARIABLE_LIST_H_INCLUDED_

#include "phi_variable.h"


typedef struct
{
    /**
     * Example:
     
        PhiVariableList list = PhiVariableList_init();
        PhiVariableList_append(&list, PhiVariable_init(String_init("name1"), PhiType_OBJ, String_init("value1")));
        PhiVariableList_append(&list, PhiVariable_init(String_init("name2"), PhiType_OBJ, String_init("value2")));
        printf("name:%s\n", PhiVariableList_at(list, 0).name);
        printf("value:%s\n", PhiVariableList_at(list, 0).value);
        printf("\n");
        printf("name:%s\n", PhiVariableList_at(list, 1).name);
        printf("value:%s\n", PhiVariableList_at(list, 1).value);
        free(list.storage);
     */
    PhiVariable* storage;
    unsigned int length;
} PhiVariableList;


PhiVariableList PhiVariableList_init();
void PhiVariableList_append(PhiVariableList* list, PhiVariable value);
PhiVariable* PhiVariableList_at(PhiVariableList list, unsigned int index);

#endif
