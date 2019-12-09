#ifndef _PHI_FUNCTION_H_INCLUDED_
#define _PHI_FUNCTION_H_INCLUDED_

#include <stdbool.h>
#include "x_string.h"
#include "phi_variable_list.h"


typedef struct
{
    String name;
    String body;  // Stores the code of the function
    PhiVariableList parameters;
    bool is_built_in;
} PhiFunction;


PhiFunction PhiFunction_init(String name);
PhiFunction PhiFunction_from_body(String body);
void PhiFunction_print(PhiFunction func);

#endif
