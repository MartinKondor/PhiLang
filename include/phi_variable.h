#ifndef _PHI_VARIABLE_H_INCLUDED_
#define _PHI_VARIABLE_H_INCLUDED_

#include "phi_type.h"
#include "x_string.h"


typedef struct
{
    String name;  // The id of the variable
    String value;
    PhiType type;
} PhiVariable;


PhiVariable PhiVariable_init(String name, PhiType type, String value);
void PhiVariable_print(PhiVariable func);

#endif
