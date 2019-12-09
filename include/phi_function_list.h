#ifndef _PHI_FUNCTION_LIST_H_INCLUDED_
#define _PHI_FUNCTION_LIST_H_INCLUDED_

#include "phi_function.h"


typedef struct
{
    PhiFunction* storage;
    unsigned int length;
} PhiFunctionList;


PhiFunctionList PhiFunctionList_init();
void PhiFunctionList_append(PhiFunctionList* list, PhiFunction value);
PhiFunction* PhiFunctionList_at(PhiFunctionList list, unsigned int index);

#endif
