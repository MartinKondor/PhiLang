#ifndef _PHI_ERROR_H_INCLUDED_
#define _PHI_ERROR_H_INCLUDED_

#include "x_string.h"


typedef struct
{
    /**
     * Error for showing exceptions and fatal errors
     */
    String msg;
    unsigned int ln_index;
    unsigned int ch_index;
} PhiError;

PhiError PhiError_init(char* msg, unsigned int ln_index, unsigned int ch_index);
void PhiError_print(PhiError err);

#endif
