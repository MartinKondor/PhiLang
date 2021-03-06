#ifndef _PHI_STACK_H_INCLUDED_
#define _PHI_STACK_H_INCLUDED_

#include "phi_type.h"
#include "phi_variable_list.h"
#include "phi_function_list.h"


typedef struct
{
    /**
     * Stores the variables and functions for a given scope.
     */
    unsigned int id;
    PhiVariableList variables;
    PhiFunctionList functions;
    PhiVariable return_value;
} PhiStack;


PhiStack PhiStack_init(unsigned int id);

/**
 * Returns variable form stack if found, else PhiVariable(type=NULL).
 */
PhiVariable* PhiStack_get_variable(PhiStack stack, String name);

/**
 * Returns variable form stack if found, else 
 * PhiVariable_init(String_init("<anonymus>"), PhiType_determine_type(name), name);.
 */
PhiVariable* PhiStack_maybe_get_variable(PhiStack stack, String name);

/**
 * Adds the contents of the right stack to the left.
 */
void PhiStack_add(PhiStack* right_stack, PhiStack* left_stack);

#endif
