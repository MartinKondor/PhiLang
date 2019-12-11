#ifndef _PHI_FUNCTION_H_INCLUDED_
#define _PHI_FUNCTION_H_INCLUDED_

#include <stdbool.h>
#include "x_string.h"
#include "x_string_list.h"
#include "phi_variable_list.h"


typedef struct
{
    String name;
    String body;  // Stores the code of the function
    StringList parameters;
    bool is_built_in;
} PhiFunction;


PhiFunction PhiFunction_init(String name);

/**
 * Parse function from body string.
 * 
 * body can be like: name(param1,param2){@"Return"!} 
 */
PhiFunction PhiFunction_from_body(String body);
void PhiFunction_print(PhiFunction func);

#endif
