#ifndef _PHI_FUNCTION_H_INCLUDED_
#define _PHI_FUNCTION_H_INCLUDED_

#include <stdbool.h>
#include "x_string.h"


typedef struct
{
    String name;
    String body;  // Stores the code of the function
    // parameters: list = []  # list[str] Parameter names
    bool is_built_in;
} PhiFunction;


PhiFunction PhiFunction_init(String text);

#endif
