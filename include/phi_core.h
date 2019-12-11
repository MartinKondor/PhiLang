#ifndef _PHI_CORE_H_INCLUDED_
#define _PHI_CORE_H_INCLUDED_


#include <stdbool.h>
#include "x_string.h"
#include "x_string_list.h"
#include "phi_error.h"
#include "phi_stack.h"
#include "phi_type.h"


/**
 * Evaluates the given Phi source code and returns
 * the main stack from it.
 */
PhiStack Phi_eval(String* code, unsigned int stack_id, PhiStack stack);

/**
 * Attempt to eval one Phi command.
 */
PhiVariable Phi_eval_command(String* command, unsigned int* ln_index, PhiStack* stack);

/**
 * Attempt to call the given function with the given parameters.
 * Rerturns the PhiVariable with the returned value of the function.
 */
PhiVariable Phi_function_call(String* token, StringList* parameters,
                        unsigned int* ln_index, unsigned int* ch_index,
                        PhiStack* stack);

/**
 * Retruns the found PhiVariable. 
 * If no variable was found, returns
 *  PhiVariable(name="<anonymus>", type=determined from name, value=name).
 */
PhiVariable Phi_maybe_get_variable(String name, PhiStack* stack);

#endif
