#ifndef _ERRORS_H_INCLUDED_
#define _ERRORS_H_INCLUDED_

#include "phi_string.h"


typedef struct
{
    String msg;
    unsigned int ln_index;
    unsigned int ch_index;
} PhiError;

void PhiError_print(PhiError err);
PhiError PhiError_init(char* msg, unsigned int ln_index, unsigned int ch_index);

#endif
