#include "phi_stack.h"


PhiStack PhiStack_init(unsigned int id)
{
    PhiStack stack;
    stack.id = id;
    stack.variables = PhiVariableList_init();
    stack.functions = PhiFunctionList_init();
    stack.return_value = PhiVariable_init(String_init("<anonymus>"), PhiType_NULL, String_init(""));
    return stack;
}

PhiVariable* PhiStack_get_variable(PhiStack stack, String name)
{
    PhiVariable* var;

    for (unsigned int i = 0; i < stack.variables.length; i++) 
    {
        var = PhiVariableList_at(stack.variables, i);

        if (strcmp(var->name.v, name.v) == 0) 
        {
            return var;
        }
    }

    *var = PhiVariable_init(String_init(""), PhiType_NULL, String_init(""));
    return var;
}

PhiVariable* PhiStack_maybe_get_variable(PhiStack stack, String name)
{
    PhiVariable* var = PhiStack_get_variable(stack, name);

    if (var->type == PhiType_NULL) {
        *var = PhiVariable_init(String_init("<anonymus>"), PhiType_determine_type(name), name);
    }
    return var;
}

void PhiStack_add(PhiStack* right_stack, PhiStack* left_stack) 
{
    // Adding functions 
    unsigned int i;

    for (i = 0; i < left_stack->functions.length; i++)
    {
        PhiFunctionList_append(&right_stack->functions, *PhiFunctionList_at(left_stack->functions, i));
    }

    for (i = 0; i < left_stack->variables.length; i++)
    {
        PhiVariableList_append(&right_stack->variables, *PhiVariableList_at(left_stack->variables, i));
    }
}
