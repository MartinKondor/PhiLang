#include "phi_core.h"


PhiStack Phi_eval(String* code, unsigned int stack_id) 
{
    PhiStack main_stack = PhiStack_init(stack_id);
    bool in_one_line_comment = false;
    bool in_string = false;
    bool in_function_def = false;
    String command = String_init("");
    unsigned int ln_index = 1;

    for (unsigned int ch_index = 0; ch_index < strlen(code->v); ch_index++) 
    {
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

        if (code->v[ch_index] == '#')
        {
            in_one_line_comment = true;
            continue;
        }

        if (code->v[ch_index] == '"')
        {
            in_string = !in_string;
        }
        
        if (in_string)
        {
            String_appendc(&command, code->v[ch_index]);
            continue;
        }

        if (code->v[ch_index] == '{') 
        {
            in_function_def = true;
            // Do not continue as we want the function body to
            // contain the whole function including the {} characters
        }

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

        if (code->v[ch_index] == '!')
        {
            if (in_string) 
            {
                PhiError_print(PhiError_init("Unclosed string.", ln_index, ch_index));
                exit(1);
            }

            Phi_eval_command(&command, &ln_index, &main_stack);
            String_clear(&command);
            continue;
        }

        String_appendc(&command, code->v[ch_index]);
    }

    return main_stack;
}

void Phi_eval_command(String* command, unsigned int* ln_index, PhiStack* stack)
{
    String token = String_init("");
    String other_token = String_init("");
    String param_token = String_init("");
    StringList parameters = StringList_init();
    unsigned int ch_index = 0;
    unsigned int other_token_index = 0;
    bool in_function_call_parameter_field = false;
    bool in_assignment = false;
    bool there_was_a_function_call = false;

    for (; ch_index < strlen(command->v); ch_index++) 
    {
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

        if (command->v[ch_index] == '(')   // Function call
        {
            in_function_call_parameter_field = true;
            continue;
        }

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

        if (in_assignment)
        {
            String_appendc(&other_token, command->v[ch_index]);
            continue;
        }
        
        String_appendc(&token, command->v[ch_index]);
    }

    if (in_assignment && there_was_a_function_call) 
    {
        Phi_function_call(&other_token, &parameters, ln_index, &ch_index, stack);
    }
    else if (in_assignment)
    {
        PhiVariableList_append(&stack->variables, PhiVariable_init(token, PhiType_determine_type(other_token), other_token));
    }
}

PhiVariable Phi_maybe_get_variable(String name, PhiStack* stack)
{
    
}

PhiVariable Phi_function_call(String* func_name, StringList* parameters, unsigned int* ln_index, unsigned int* ch_index, PhiStack* stack)
{
    PhiVariable var;
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

    if (strcmp(func.name.v, "<anonymus>") == 0)
    {
        char msg[36 + strlen(func_name->v)];
        sprintf(msg, "Undefined reference to function \"%s\".\n", func_name->v);
        PhiError_print(PhiError_init(msg, *ln_index, *ch_index));
        exit(1);
    }

    if (parameters->length != func.parameters.length)
    {
        char msg[45 + strlen(func_name->v)];
        sprintf(msg, "Wrong number of parameters for function \"%s\".\n", func_name->v);
        PhiError_print(PhiError_init(msg, *ln_index, *ch_index));
        exit(1);
    }

    StringList parameter_values = StringList_init();
    
    for (i = 0; i < parameters->length; i++) 
    {
        StringList_append(&parameter_values, Phi_maybe_get_variable(*StringList_at(*parameters, i), stack).value);
    }

    for (i = 0; i < parameter_values.length; i++)
    {
        printf("((%s))\n", StringList_at(parameter_values, i)->v);
    }

    // TODO: Eval function body
    return var;
}
