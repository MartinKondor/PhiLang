#ifndef _PHI_VARIABLE_H_INCLUDED_
#define _PHI_VARIABLE_H_INCLUDED_

#include "phi_type.h"
#include "phi_string.h"


typedef struct
{
    String name;
    String value;
    PhiType type;
} PhiVariable;


PhiVariable PhiVariable_init(String name, PhiType type, String value);

#endif
