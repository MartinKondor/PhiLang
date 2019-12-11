#include "phi_core.h"


PhiStack Phi_eval(String* code, unsigned int stack_id, PhiStack stack) 
{
    PhiStack main_stack = PhiStack_init(stack_id);

    // Add the contents of the previous stack to the current stack.
    PhiStack_add(&main_stack, &stack);

    bool in_one_line_comment = false;
    bool in_string = false;
    bool in_function_def = false;
    String command = String_init("");
    unsigned int ln_index = 1;

    for (unsigned int ch_index = 0; ch_index < strlen(code->v); ch_index++) 
    {
        // Count lines and turn off in_one_line_comment
        if (code->v[ch_index] == '\n')
        {
            ln_index++;
            if (in_one_line_comment)
            {
                in_one_line_comment = false;
            }
            if (!in_string) continue;  // Enable newline in strings
        }

        if (in_one_line_comment || (code->v[ch_index] == ' ' && !in_string)) 
        {
            continue;
        }

        // Comments
        if (code->v[ch_index] == '#')
        {
            in_one_line_comment = true;
            continue;
        }

        // Strings
        if (code->v[ch_index] == '"')
        {
            in_string = !in_string;
        }

        // Add to command here, as we don't want to skip
        // any character in strings.        
        if (in_string)
        {
            String_appendc(&command, code->v[ch_index]);
            continue;
        }

        // Start of function definition
        if (code->v[ch_index] == '{') 
        {
            in_function_def = true;
            // Do not continue as we want the function body to
            // contain the whole function including the {} characters
        }

        // End of function definition
        if (code->v[ch_index] == '}')
        {
            if (!in_function_def)
            {
                PhiError_print(PhiError_init("Unopened function definition.", ln_index, ch_index));
                exit(1);
            }

            in_function_def = false;
            String_append(&command, "}");

            // Add function to stack
            PhiFunctionList_append(&main_stack.functions, PhiFunction_from_body(command));
            String_clear(&command);
            continue;
        }

        if (in_function_def)
        {
            String_appendc(&command, code->v[ch_index]);
            continue; 
        }

        // End of statement character,
        // evaluate the current "command".
        if (code->v[ch_index] == '!')
        {
            if (in_string) 
            {
                PhiError_print(PhiError_init("Unclosed string.", ln_index, ch_index));
                exit(1);
            }

            // Eval command and get the returned value from it
            PhiVariable return_value = Phi_eval_command(&command, &ln_index, &main_stack);
            String_clear(&command);

            // If not null there were a return value, which we return here
            if (return_value.type != PhiType_NULL)
            {
                main_stack.return_value = return_value;
                break;
            }
            continue;
        }

        // Add character to command
        String_appendc(&command, code->v[ch_index]);
    }

    return main_stack;
}

PhiVariable Phi_eval_command(String* command, unsigned int* ln_index, PhiStack* stack)
{
    PhiVariable return_value = PhiVariable_init(String_init("<anonymus>"), PhiType_NULL, String_init(""));;
    String token = String_init("");
    String other_token = String_init("");
    String param_token = String_init("");
    StringList parameters = StringList_init();
    unsigned int ch_index = 0;
    unsigned int other_token_index = 0;
    bool in_function_call_parameter_field = false;
    bool in_assignment = false;
    bool there_was_a_function_call = false;
    bool in_return_value = false;

    for (; ch_index < strlen(command->v); ch_index++)
    {
        // Return statement
        if (command->v[ch_index] == '@')
        {
            in_return_value = true;
            continue;
        }

        // Its an assignment
        if (command->v[ch_index] == '=')
        {
            if (in_assignment)
            {
                PhiError_print(PhiError_init("Unexpected character \"=\".", *ln_index, ch_index));
                exit(1);
            }

            in_assignment = true;
            continue;
        }

        // Function call    
        if (command->v[ch_index] == '(')   
        {
            in_function_call_parameter_field = true;
            continue;
        }

        // End of function call
        if (command->v[ch_index] == ')')
        {
            if (!in_function_call_parameter_field)
            {
                PhiError_print(PhiError_init("Unexpected character \")\".", *ln_index, ch_index));
                exit(1);
            }

            // Add last parameter if there is
            if (strlen(param_token.v) != 0)
            {
                StringList_append(&parameters, param_token);
                String_clear(&param_token);
            }
            
            in_function_call_parameter_field = false;
            there_was_a_function_call = true;
            continue;
        }

        // Add parameters to an array to keep
        // track of parameters.
        if (in_function_call_parameter_field)
        {
            if (command->v[ch_index] == ',')
            {
                StringList_append(&parameters, param_token);
                String_clear(&param_token);
                continue;
            }

            String_appendc(&param_token, command->v[ch_index]);
            continue;
        }

        // Add char to other_token
        if (in_assignment)
        {
            String_appendc(&other_token, command->v[ch_index]);
            continue;
        }
        
        String_appendc(&token, command->v[ch_index]);
    }

    // Create a varialbe with thre result of the function call
    // then save the variable.
    if (in_assignment && there_was_a_function_call) 
    {
        PhiVariable func_result = Phi_function_call(&other_token, &parameters, ln_index, &ch_index, stack);
        PhiVariable new_var = PhiVariable_init(token, func_result.type, func_result.value);
        PhiVariableList_append(&stack->variables, new_var);
        if (in_return_value) return func_result;
    }
    else if (in_assignment)
    {
        PhiVariable value = PhiVariable_init(token, PhiType_determine_type(other_token), other_token);

        // Turn true and false into 1 and 0
        if (value.type == PhiType_NUM)
        {
            if (strcmp(value.value.v, "true") == 0) value.value = String_init("1");
            if (strcmp(value.value.v, "false") == 0) value.value = String_init("0");
        }

        PhiVariableList_append(&stack->variables, value);
        if (in_return_value) return value;
    }

    // Set the return_value
    if (in_return_value)
    {
        return_value = Phi_maybe_get_variable(token, stack);
    }
    return return_value;
}

PhiVariable Phi_maybe_get_variable(String name, PhiStack* stack)
{
    unsigned int i;

    // Try to find the variable in the stack
    for (i = 0; i < stack->variables.length; i++)
    {
        if (strcmp(PhiVariableList_at(stack->variables, i)->name.v, name.v) == 0)
        {
            return *PhiVariableList_at(stack->variables, i);
        }
    }

    // Return anonymus value if nothing found
    PhiVariable result = PhiVariable_init(String_init("<anonymus>"), PhiType_OBJ, name);
    return result;
}

PhiVariable Phi_function_call(String* func_name, StringList* parameters, unsigned int* ln_index, unsigned int* ch_index, PhiStack* stack)
{
    PhiFunction func = PhiFunction_init(String_init("<anonymus>"));
    unsigned int i;

    // Check function in stack in case of undefined function
    for (i = 0; i < stack->functions.length; i++) 
    {
        if (strcmp(PhiFunctionList_at(stack->functions, i)->name.v, func_name->v) == 0)
        {
            func = *PhiFunctionList_at(stack->functions, i);
            break;
        }
    }

    // There is no function with this name
    if (strcmp(func.name.v, "<anonymus>") == 0)
    {
        char msg[36 + strlen(func_name->v)];
        sprintf(msg, "Undefined reference to function \"%s\".\n", func_name->v);
        PhiError_print(PhiError_init(msg, *ln_index, *ch_index));
        exit(1);
    }

    // Unpropper number of parameters
    if (parameters->length != func.parameters.length)
    {
        char msg[45 + strlen(func_name->v)];
        sprintf(msg, "Wrong number of parameters for function \"%s\".\n", func_name->v);
        PhiError_print(PhiError_init(msg, *ln_index, *ch_index));
        exit(1);
    }

    // Save the value of the parameters
    // e.g if the parameter is a variable get the value of it    
    PhiVariable var;
    PhiStack base_func_stack = PhiStack_init(stack->id + 1);

    for (i = 0; i < parameters->length; i++)
    {
        var = Phi_maybe_get_variable(*StringList_at(*parameters, i), stack);

        if (strcmp(var.name.v, "<anonymus>") == 0)
        {
            var.name = *StringList_at(func.parameters, i);
            var.type = PhiType_determine_type(var.value);
        }

        // Add parameter to stack as a variable 
        // for use in function body
        PhiVariableList_append(&base_func_stack.variables, var);
    }

    // Eval function body
    PhiStack func_stack = Phi_eval(&func.body, stack->id + 1, base_func_stack);
    return func_stack.return_value;
}
