#ifndef _PHI_CORE_H_INCLUDED_
#define _PHI_CORE_H_INCLUDED_


#include <stdbool.h>
#include "x_string.h"
#include "phi_error.h"
#include "phi_stack.h"


/**
 * Evaluates the given Phi source code and returns
 * the main stack from it.
 */
PhiStack Phi_eval(String code, unsigned int stack_id);

#endif
