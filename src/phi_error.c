#include "phi_error.h"


PhiError PhiError_init(char* msg, unsigned int ln_index, unsigned int ch_index)
{
    PhiError error;
    error.msg = String_init(msg);
    error.ln_index = ln_index;
    error.ch_index = ch_index;
    return error;
}

void PhiError_print(PhiError err)
{
    printf("Error (%u:%u):\n%s", err.ln_index, err.ch_index, err.msg);
}
