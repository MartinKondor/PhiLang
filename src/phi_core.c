#include "phi_core.h"


PhiStack Phi_eval(String code, unsigned int stack_id) 
{
    bool in_string = false;
    bool in_one_line_comment = false;
    bool in_function_def = false;
    String command = String_init("");
    unsigned int ln_index = 1;
    PhiStack main_stack = PhiStack_init(stack_id);
    char ch;

    for (unsigned int ch_index = 0; ch_index < strlen(code.v); ch_index++) 
    {
        ch = code.v[ch_index];

        if (ch == '\n') 
        {
            ln_index++;
            if (in_one_line_comment)
            {
                in_one_line_comment = false;
            }
            continue;
        }

        if (in_one_line_comment || (ch == ' ' && !in_string)) 
        {
            continue;
        }

        if (ch == '#')
        {
            in_one_line_comment = true;
            continue;
        }
        
        if (ch == '"')
        {
            in_string = !in_string;
        }
        
        if (in_string)
        {
            String_appendc(&command, ch);
            continue;
        }

        if (ch == '{') 
        {
            in_function_def = true;
        }

        if (ch == '}') 
        {
            if (!in_function_def) 
            {
                PhiError_print(PhiError_init("Unopened function definition.", ln_index, ch_index));
                exit(1);
            }

            in_function_def = false;
            String_append(&command, "}");
            PhiFunctionList_append(&main_stack.functions, PhiFunction_from_body(command));
            String_clear(&command);
            continue;
        }

        if (in_function_def)
        {
            String_appendc(&command, ch);
            continue; 
        }

        if (ch == '!') 
        {
            if (in_string) 
            {
                PhiError_print(PhiError_init("Unclosed string.", ln_index, ch_index));
                exit(1);
            }

            Phi_eval_command(&command, ln_index, &main_stack);
            String_clear(&command);
            continue;
        }

        String_appendc(&command, ch);
    }

    return main_stack;
}

void Phi_eval_command(String* command, unsigned int ln_index, PhiStack* stack)
{
    PhiVariableList parameters = PhiVariableList_init();
    bool in_function_call_parameter_field = false;

    String token = String_init("");
    String other_token = String_init("");
    bool in_assignment = false;
    char ch;

    unsigned int ch_index = 0;

    for (; ch_index < strlen(command->v); ch_index++) 
    {
        ch = command->v[ch_index];
        
        // Process parameters of function call
        if (in_function_call_parameter_field) 
        {
            if (ch == ',')
            {
                PhiVariableList_append(&parameters, PhiVariable_init(token, PhiType_determine_type(other_token), other_token));
                String_clear(&other_token);
            }

            String_appendc(&other_token, ch);
            continue;
        }

        if (ch == '=')
        {
            if (in_assignment && strlen(other_token.v) == 0)
            {
                PhiError_print(PhiError_init("Unexpected \"=\" operator.", ln_index, ch_index));
                exit(1);
            }

            in_assignment = true;
            String_clear(&other_token);
            continue;
        }

        if (ch == '(')
        {
            in_function_call_parameter_field = true;
            continue;
        }

        if (in_assignment)
        {
            String_appendc(&other_token, ch);
            continue;
        }

        String_appendc(&token, ch);
    }

    if (in_assignment)
    {
        // PhiVariableList_append(&stack->variables, PhiVariable_init(token, PhiType_determine_type(other_token), other_token));
    }

    if (in_function_call_parameter_field)
    {
        if (strlen(other_token.v) != 0)
        {
            // Remove the last element
            // parameters.length--;
            // PhiVariableList_append(&parameters, PhiVariable_init(String_init("<anonymus>"), PhiType_determine_type(other_token), other_token));
        }

        Phi_function_call(&token, &parameters, ln_index, ch_index, stack);
    }

}

void Phi_function_call(String* token, PhiVariableList* parameters, unsigned int ln_index, unsigned int ch_index, PhiStack* stack)
{
    // PhiFunction func;
}
