#ifndef _PHI_TYPE_H_INCLUDED_
#define _PHI_TYPE_H_INCLUDED_

#include "phi_string.h"


typedef enum 
{
    PhiType_NULL,
    PhiType_OBJ,  // Inherited by everything
    PhiType_STR,
    PhiType_NUM,
    PhiType_LIST
} PhiType;


/**
 * Determines the PhiType of the given string.
 */
PhiType determine_type(String value);

#endif
